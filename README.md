# **minishell:** 
## ***A 42 project... :***
[Subject][1]
## Goal:

- [x] No memory leaks

The goal of this project is to make our own version of [bash][2]. It must be able to handle basic features such as :

- Execute all bash command
- Use redirection ***"<" "<<" ">"***
- Pipe "|"
- colons ";"
- " and ' (You should not be able to handle open quote)
- The following builtin **_MUST_** be implemented by yourself :

|  echo          |       cd        |      pwd       |    export      | unset          | env            | exit           |
| -------------- | --------------- | -------------- | -------------- | -------------- | -------------- | -------------- |
| With -n option | With no option  | With no option | With no option | With no option | With no option | With no option |

## Final grade:
100/100

### Nota bene:
I didnt do termcaps and history gestion with up and down arrow.


[1]: https://github.com/fleger42/minishell_liste/blob/master/minishell_pdf.pdf
[2]: https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
