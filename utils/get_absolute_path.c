#include "../includes/minishell.h"

char    *get_absolute_path(char *cmd)
{
	char	*path = strdup(getenv("PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;

	if (path == NULL) // si le path est null, on cree un path
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	// si cmd n'est pas le chemin absolue, on cherche le chemin absolue du
	// binaire grace a la variable d'environment PATH
	if (cmd[0] != '/' && strncmp(cmd, "./", 2) != 0) {

		// On split le path pour verifier ou ce trouve le binaire
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;

		// On boucle sur chaque dossier du path pour trouver l'emplacement du binaire
		for (int i = 0; path_split[i]; i++) {
			// alloc len du path + '/' + len du binaire + 1 pour le '\0'
			bin = (char *)calloc(sizeof(char), (strlen(path_split[i]) + 1 + strlen(cmd) + 1));
			if (bin == NULL)
				break ;

			// On concat le path , le '/' et le nom du binaire
			strcat(bin, path_split[i]);
			strcat(bin, "/");
			strcat(bin, cmd);

			// On verfie l'existence du fichier et on quitte la boucle si access
			// renvoi 0
			if (access(bin, F_OK) == 0)
				break ;

			// Nous sommes des gens propre :D
			free(bin);
			bin = NULL;
		}
		//free_array(path_split);

		// On remplace le binaire par le path absolue ou NULL si le binaire
		// n'existe pas
		//free(cmd);
		cmd = bin;
	} else {
		free(path);
		path = NULL;
	}
    return cmd;
}