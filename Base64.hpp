#ifndef BASE_64
#define BASE_64


#include	<string>
/*
 * =====================================================================================
 *        Class:  Base64
 *  Description:  Permet d'encoder une chaine de caractères en base64
 *                Il n'y pas de fonction decode pour le moment
 * =====================================================================================
 */
class Base64 {

	/*
	 * ===  FUNCTION  ======================================================================
	 *         Name:  encode
	 *  Description:  Permet d'encoder une chaine de caractère en base64
	 *   Paramètres:  normal -> chaine de caractère à encoder
	 *                taille -> taille de la chaine de caractère à encoder
	 * =====================================================================================
	 */
public:
	static char* encode ( const unsigned char* chaine, const int tailleChaine );
	static char* encode ( std::string nomFichier );

};

#endif
