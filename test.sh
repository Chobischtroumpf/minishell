bash -c "echo $PWD; echo $OLDPWD; cd ..; pwd; echo $PWD; echo $OLDPWD"

./minishell -c "echo $PWD; echo $OLDPWD; cd ..; pwd; echo $PWD; echo $OLDPWD"
