# minishell

Your shell should: <br />
β’ Not interpret unclosed quotes or unspecified special characters like \ or ; π’<br />
β’ Not use more than one global variable, think about it and be ready to explain why you do it π’<br />
β’ Show a prompt when waiting for a new command π’ <br />
β’ Have a working History π’ <br /> 
β’ Search and launch the right executable (based on the PATH variable or by using relative or absolute path) π’ <br />
β¦ echo with option -n π’ <br />
β¦ cd with only a relative or absolute path  π’<br />
β¦ pwd with no options π’ <br />
β¦ export with no options π’ <br />
β¦ unset with no options π’ <br />
β¦ env with no options or arguments π’ <br />
β¦ exit with no options π’ <br />
β’ β inhibit all interpretation of a sequence of characters π’ <br />
β’ " inhibit all interpretation of a sequence of characters except for $ π’<br />
β¦ < should redirect input. <br />
β¦ > should redirect output. <br />
β¦ β<<β read input from the current source until a line containing only the de- limiter is seen. it doesnβt need to update history! <br />
β¦ β>>β should redirect output with append mode. <br />
β’ Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command. <br />
β’ Environment variables ($ followed by characters) should expand to their values π’ <br />
β’ $? should expand to the exit status of the most recently executed foreground pipeline π’ <br />
β¦ ctrl-C print a new prompt on a newline π’<br />
β¦ ctrl-D exit the shell π’ <br />
β¦ ctrl-\ do nothing π’ <br />
