# **minishell:** 
## ***A 42 project... :***
[Subject][1]
## Requirment:
You must be on a Linux distribution.
## Goal:

- [x] No memory leaks
- [x] Norm

The goal of this project is to make our own version of [bash][2]. It must be able to handle basic features such as :

- Execute all bash command
- Prompt printing
- Use redirection ***"<" "<<" ">"***
- Pipe "|"
- colons ";"
- " and ' (You should not be able to handle open quote)
- $? (exit value)
- Environnement variable `Exemple: export date=2021 ; echo $date`
- Environnement variable like `SHLVL`, `PWD`, `OLDPWD` must be updated when necessary
- The following signal must be handled like bash :

|  Ctrl-C       |       Ctrl-\     |      Ctrl-D    |
| -------------- | --------------- | -------------- |
| Send SINGINT   | Send SIGQUIT    | Send EOF       | 

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
