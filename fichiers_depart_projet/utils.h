/* Yana Nashchetska 12417961 ERASMUS
Je déclare qu'il s'agit de mon propre travail.
Ce travail a été réalisé intégralement par un être humain. */

/*Note :
le code a été écrit à l'aide de modèles dans Moodle, 
en complément du code existant.*/

#ifndef UTILS_H
#define UTILS_H value

/* Changer une ligne se terminant par CRLF en une ligne se terminant par LF.
 * La ligne doit être terminée par un carcactère nul.
 * Retourne la ligne modifiée ou NULL en cas d'erreur. */
char *crlf_to_lf(char *line_with_crlf);

/* Changer une ligne se terminant par LF en une ligne se terminant par CRLF.
 * La ligne doit être terminée par un carcactère nul.
 * Attention, l'utilisateur doit vérifier que le tableau peut contenir
 * un caractère supplémentaire.
 * Retourne la ligne modifiée ou NULL en cas d'erreur. */
char *lf_to_crlf(char *line_with_lf);
#endif /* ifndef UTILS_H */
