/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isiboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 22:09:27 by isiboub           #+#    #+#             */
/*   Updated: 2025/10/24 22:18:27 by isiboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

/*
{
ASSERT_EQ_STR("ft_strchr char exists", ft_strchr("hello", 'e'), strchr("hello", 'e'));
ASSERT_EQ_STR("ft_strchr not exist", ft_strchr("hello", 'z'), strchr("hello", 'z'));
ASSERT_EQ_STR("ft_strrchr exists", ft_strrchr("abca", 'a'), strrchr("abca", 'a'));


ASSERT_EQ_INT("ft_strncmp equal", ft_strncmp("abc", "abc", 3), strncmp("abc","abc",3));
ASSERT_EQ_INT("ft_strncmp diff", (ft_strncmp("abc","abd",3) < 0), (strncmp("abc","abd",3) < 0));
}


/* 5. atoi */
static void test_atoi(void)
{
ASSERT_EQ_INT("ft_atoi simple", ft_atoi("42"), atoi("42"));
ASSERT_EQ_INT("ft_atoi spaces", ft_atoi("\t\n -123"), atoi("\t\n -123"));
ASSERT_EQ_INT("ft_atoi zero", ft_atoi("0"), atoi("0"));
/* Overflow detection: behavior of atoi is undefined on overflow, but compare sign where possible */
ASSERT_EQ_INT("ft_atoi large", ft_atoi("2147483648"), atoi("2147483648"));
}


/* 6. calloc */
static void test_calloc(void)
{
void *p = ft_calloc(5, 4);
if (!p) { report("ft_calloc alloc", 0, "returned NULL"); return; }
int ok = 1;
unsigned char *q = (unsigned char*)p;
for (size_t i = 0; i < 20; ++i) if (q[i] != 0) { ok = 0; break; }
free(p);
report("ft_calloc zeros", ok, ok ? NULL : "not zeroed");


/* calloc overflow: try a large size - run in child to avoid crash */
void child_test(void)
{
void *r = ft_calloc(SIZE_MAX, SIZE_MAX);
(void)r;
}
int res = run_isolated(child_test);
if (res == 2) report("ft_calloc overflow (crash)", 0, "crashed"); else report("ft_calloc overflow (no crash)", 1, NULL);
}


/* 7. strdup */
static void test_strdup(void)
{
char *s = ft_strdup("hello world");
if (!s) { report("ft_strdup alloc", 0, "NULL"); return; }
ASSERT_EQ_STR("ft_strdup content", s, "hello world");
free(s);
}


/* 8. Part 2 string alloc functions: substr, strjoin, strtrim, split, itoa */
static void test_part2_strings(void)
{
char *sub = ft_substr("Hello", 1, 3); ASSERT_EQ_STR("ft_substr basic", sub, "ell"); free(sub);


char *join = ft_strjoin("Hello", "World"); ASSERT_EQ_STR("ft_strjoin basic", join, "HelloWorld"); free(join);


char *trim = ft_strtrim(" \tHello \n ", " \n\t"); ASSERT_EQ_STR("ft_strtrim basic", trim, "Hello"); free(trim);


char **arr = ft_split("one two three", ' ');
if (!arr) { report("ft_split alloc", 0, "NULL"); }
else
{
int ok = 1;
if (!arr[0] || strcmp(arr[0], "one") != 0) ok = 0;
if (!arr[1] || strcmp(arr[1], "two") != 0) ok = 0;
if (!arr[2] || strcmp(arr[2], "three") != 0) ok = 0;
if (arr[3] != NULL) ok = 0;
report("ft_split basic", ok, ok?NULL:"contents mismatch");
for (int i = 0; arr[i]; ++i) free(arr[i]);
free(arr);
}


char *num = ft_itoa(-2147483648); ASSERT_EQ_STR("ft_itoa minint", num, "-2147483648"); free(num);
}


/* 9. strlcpy / strlcat */
static void test_strl(void)
{
char dst1[10]; char dst2[10];
memset(dst1, 'X', sizeof(dst1)); memset(dst2, 'X', sizeof(dst2));
size_t r1 = ft_strlcpy(dst1, "Hello", sizeof(dst1));
size_t r2 = strlcpy(dst2, "Hello", sizeof(dst2));
if (r1==r2 && strcmp(dst1,dst2)==0) report("ft_strlcpy", 1, NULL); else report("ft_strlcpy", 0, "mismatch");


memset(dst1, 'X', sizeof(dst1)); memset(dst2, 'X', sizeof(dst2));
size_t c1 = ft_strlcat(dst1, "World", sizeof(dst1));
size_t c2 = strlcat(dst2, "World", sizeof(dst2));
if (c1==c2 && strcmp(dst1,dst2)==0) report("ft_strlcat", 1, NULL); else report("ft_strlcat", 0, "mismatch");
}


/* 10. Linked list bonus: create, add, size, last, del, clear, iter, map */
static void test_list_bonus(void)
{
t_list *a = ft_lstnew(strdup("a"));
t_list *b = ft_lstnew(strdup("b"));
t_list *c = ft_lstnew(strdup("c"));
ft_lstadd_back(&a, b);
ft_lstadd_back(&a, c);
int size = ft_lstsize(a);
ASSERT_EQ_INT("ft_lstsize", size, 3);
t_list *last = ft_lstlast(a);
if (last && last->content && strcmp((char*)last->content, "c") == 0) report("ft_lstlast", 1, NULL); else report("ft_lstlast", 0, "wrong last");


/* iter: uppercase contents */
void to_upper(void *p) { char *s = p; for (int i=0; s[i]; ++i) s[i] = toupper(s[i]); }
ft_lstiter(a, to_upper);
if (strcmp((char*)a->content, "A") == 0) report("ft_lstiter", 1, NULL); else report("ft_lstiter", 0, "iter failed");


/* map: append ! to each string */
void *append_excl(void *p)
{
char *s = p;
size_t len = strlen(s);
char *r = malloc(len + 2);
strcpy(r, s); r[len] = '!'; r[len+1] = '\0';
return r;
}
t_list *mapped = ft_lstmap(a, append_excl, free);
if (mapped && mapped->next && mapped->next->next) report("ft_lstmap", 1, NULL); else report("ft_lstmap", 0, "map failed");


ft_lstclear(&a, free);
ft_lstclear(&mapped, free);
}


/* 11. Edge-case and NULL handling tested in isolated children */
static void test_null_and_edgecases(void)
{
/* Many libft functions are undefined on NULL input; but testers sometimes expect
functions like ft_strlen(NULL) to crash. We'll run a few calls in child processes
to ensure library does not crash unexpectedly when some projects forbid NULL handling.
*/
void child1(void) { (void)ft_strlen(NULL); }
int r1 = run_isolated(child1);
if (r1 == 2) report("ft_strlen(NULL) crashed", 1, NULL); else report("ft_strlen(NULL) crashed", 0, "did not crash (or returned) - check expected behavior");


void child2(void) { (void)ft_strcpy(NULL, NULL); } /* many libft's don't implement strcpy but if user has it */
/* skip if not available - we check at compile time by presence */
#ifdef FT_STRCPY
int r2 = run_isolated(child2);
if (r2 == 2) report("ft_strcpy(NULL,NULL) crashed", 1, NULL); else report("ft_strcpy(NULL,NULL) crash", 0, "did not crash");
#endif
}


int main(void)
{
fprintf(stderr, "Running full libft tester...\n");


test_is_functions();
test_strlen();
test_memory_funcs();
test_string_search_cmp();
test_atoi();
test_calloc();
test_strdup();
test_part2_strings();
test_strl();
test_list_bonus();
/* NULL/edgecases */
/* test_null_and_edgecases(); -- commented because behavior expectations differ per student */


fprintf(stderr, "\nTests run: %d | Failed: %d\n", tests_run, tests_failed);
return (tests_failed == 0) ? 0 : 1;
}
