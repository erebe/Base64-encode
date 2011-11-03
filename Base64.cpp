#include	<fstream>
#include    "Base64.hpp"
using namespace std;

char *Base64::encode ( const unsigned char *normal, const int taille ) {

    /*-----------------------------------------------------------------------------
     *  Declaration des variables
     *-----------------------------------------------------------------------------*/
    int taille_enc;
    char *enc;
    char *enc_temp;
    const unsigned char val[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

    /*-----------------------------------------------------------------------------
     *  Calcul de la longeur de la chaine une fois transformé en base64
     *-----------------------------------------------------------------------------*/
    if ( taille % 3 != 0 )
        taille_enc =
            ( taille + ( 3 - ( taille % 3 ) ) ) +
            ( ( taille + ( 3 - ( taille % 3 ) ) ) / 3 ) + 1;
    else
        taille_enc = ( taille ) + ( taille / 3 ) + 1;

    /*-----------------------------------------------------------------------------
     *  Allocation de la memoire pour la nouvelle chaine de caractère
     *-----------------------------------------------------------------------------*/
    enc = new char[taille_enc];
    enc_temp = new char[taille_enc + taille_enc / 34 + 1];

    /*-----------------------------------------------------------------------------
     *  On converti toute la chaine jusqu'au dernier multiple de 3 possible
     *-----------------------------------------------------------------------------*/
    for ( int i = 0, j = 0; j < ( taille - ( taille % 3 ) ); i += 4, j += 3 ) {
        enc[i] = normal[j] >> 2;
        enc[i + 1] = ( ( normal[j] & 0x3 ) << 4 ) | ( normal[j + 1] >> 4 );
        enc[i + 2] = ( normal[j + 1] & 0x0F ) << 2 | ( normal[j + 2] >> 6 );
        enc[i + 3] = ( normal[j + 2] & 0x3F );
    }

    /*-----------------------------------------------------------------------------
     *  On traite separement les 3 derniers octects non multiple
     *-----------------------------------------------------------------------------*/
    if ( taille % 3 == 1 ) {
        enc[taille_enc - 5] = ( normal[taille - 1] & 0x3 ) << 4;
        enc[taille_enc - 4] = normal[taille - 1] >> 2;
        enc[taille_enc - 3] = 64;
        enc[taille_enc - 2] = 64;
    }
    if ( taille % 3 == 2 ) {
        enc[taille_enc - 5] = normal[taille - 2] >> 2;
        enc[taille_enc - 4] =
            ( ( normal[taille - 2] & 0x3 ) << 4 ) | ( normal[taille - 1] >> 4 );
        enc[taille_enc - 3] = ( normal[taille - 1] & 0x0F ) << 2;
        enc[taille_enc - 2] = 64;
    }

    enc[taille_enc - 1] = '\0';

    /*-----------------------------------------------------------------------------
     *  On fait la correspondance des nombres avec la table de hash
     *-----------------------------------------------------------------------------*/
    for ( int i = 0; i < taille_enc - 1; i++ )
        enc[i] = val[( unsigned short int ) enc[i]];

    /*-----------------------------------------------------------------------------
     *  On rajoute tous les 76 caractères un saut de ligne (Roundcube fait chier sinon)
     *-----------------------------------------------------------------------------*/
    for ( int i = 0, j = 0; i < taille_enc - 1; ++i, ++j ) {
        if ( i % 77 == 0 ) {
            enc_temp[j] = '\r';
            enc_temp[++j] = '\n';
            enc_temp[++j] = enc[i];
        }
        else
            enc_temp[j] = enc[i];
    }

    /*-----------------------------------------------------------------------------
     *  On desalloue la mémoire que l'on utilise plus
     *-----------------------------------------------------------------------------*/
    delete enc;

    return enc_temp;             /* Attention, l'utilisateur doit se charger de la gestion de la mémoire */
}


char* Base64::encode( string nomFichier ) {

	char *chaineEncode;
	char *buffer;
	unsigned int taille;

	ifstream fichier( nomFichier.c_str(), ios::in | ios::binary );

	if ( !fichier.is_open() )
        throw ios_base::failure( "Impossible d'ouvrir le fichier " + nomFichier );

    /*-----------------------------------------------------------------------------
     *  On determine la taille de la chaine à allouer
     *-----------------------------------------------------------------------------*/
	fichier.seekg( 0, ios::end );
	taille = fichier.tellg( );
	fichier.seekg( 0, ios::beg );

	buffer = new char[taille];


	fichier.read( buffer, taille );
	fichier.close( );

    /*-----------------------------------------------------------------------------
     *  On encode le fichier
     *-----------------------------------------------------------------------------*/
	chaineEncode = Base64::encode( (unsigned char *) buffer, taille);
	delete[]buffer;



	return chaineEncode;

}
