#include "../includes/minishell.h"

void replace_all_key(t_shell *shell){
    int i;
    int found;
    int start;
    int end;

    found = 0;
    start = -1;
    end = -1;
    i = 0;
    while (i <= (int)ft_strlen(shell->command_line_clean)){
        if (found){
            if (!ft_isalnum(shell->command_line_clean[i]) && shell->command_line_clean[i] != '_'){
                end = i;
                found = false;
                replace(shell, start, end);
            }

        }
        if (shell->command_line_clean[i] == '$' && !is_index_is_between_single_quote(i, shell)){
            if (shell->command_line_clean[i + 1] == '?'){
                replace2(shell, i, i+2);
            } else {
                found = 1;
                start = i;
                end = -1;
            }
        }
        i++;
    }

}

int replace(t_shell *shell, int start, int end)
{
    char *phrase;
    char *oldW;
    char *key;
    char *newW;

    phrase = shell->command_line_clean;
    oldW = ft_substr_clean(shell, phrase, start, end - start);
    key = oldW + 1;
    newW = ft_strdup_clean(shell, "");
    if (env_key_exist(key, shell))
        newW = get_env_object(key, shell)->value;
    shell->command_line_clean = replaceWord(phrase, oldW, newW, shell);
    return 1;
}

int replace2(t_shell *shell, int start, int end)
{
    char *phrase;
    char *oldW;
    char *key;
    char *newW;

    phrase = shell->command_line_clean;
    oldW = ft_substr_clean(shell, phrase, start, end - start);
    key = oldW + 1;
    newW = ft_strdup_clean(shell, ft_itoa_clean(shell, shell->error_return));
    shell->command_line_clean = replaceWord(phrase, oldW, newW, shell);
    return 1;
}

char* replaceWord(const char* s, const char* oldW,
                  const char* newW, t_shell *shell)
{
    char* result;
    int i = 0;
    int cnt = 0;
    int newWlen = ft_strlen(newW);
    int oldWlen = ft_strlen(oldW);
  
    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
  
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
    cnt = 1;
    // Making new string of enough length
    result = (char*)ft_safe_malloc(i + cnt * (newWlen - oldWlen) + 1, shell);
  
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (cnt && strstr(s, oldW) == s && !is_index_is_between_single_quote(i, shell)) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
            cnt = 0;
        }
        else
            result[i++] = *s++;
    }
  
    result[i] = '\0';
    return result;
}