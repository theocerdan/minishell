# minishell

https://segfault42.github.io/posts/minishell/

Your shell should: <br />
• Not interpret unclosed quotes or unspecified special characters like \ or ;. <br />
• Not use more than one global variable, think about it and be ready to explain why you do it. <br />
• Show a prompt when waiting for a new command. <br />
• Have a working History. 🔵 <br /> 
• Search and launch the right executable (based on the PATH variable or by using relative or absolute path) <br />
   • It must implement the builtins: <br />
     ◦ echo with option -n <br />
     ◦ cd with only a relative or absolute path ◦ pwd with no options <br />
     ◦ export with no options <br />
     ◦ unset with no options <br />
     ◦ env with no options or arguments ◦ exit with no options <br />
• ’ inhibit all interpretation of a sequence of characters. <br />
• " inhibit all interpretation of a sequence of characters except for $. <br />
  • Redirections: <br />
   ◦ < should redirect input. <br />
   ◦ > should redirect output. <br />
   ◦ “<<” read input from the current source until a line containing only the de- limiter is seen. it doesn’t need to update history! <br />
   ◦ “>>” should redirect output with append mode. <br />
• Pipes | The output of each command in the pipeline is connected via a pipe to the
input of the next command. <br />
• Environment variables ($ followed by characters) should expand to their values. <br />
• $? should expand to the exit status of the most recently executed foreground pipeline. <br />
• ctrl-C ctrl-D ctrl-\ should work like in bash. <br />
  • When interactive: <br />
    ◦ ctrl-C print a new prompt on a newline. ◦ ctrl-D exit the shell. <br />
    ◦ ctrl-\ do nothing. <br />
