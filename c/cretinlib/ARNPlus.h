

# ifndef __CRETINLIB_ARNPLUS__
# define __CRETINLIB_ARNPLUS__

# include "ARN.h"
# include "LDC.h"


/**
 * \brief    Donne les éléments d'un ARN sous forme de LDC (triée, croissante)
 */
LDC ARN_lister(ARN arn);

/**
 * \brief    Crée un ARN avec une LDC
 * \param    ldc  La LDC contenant les éléments
 * \param    eval La fonction d'évaluation
 */
ARN ARN_fromLDC(LDC ldc, ARNElementEval eval);

/**
 * \brief    Crée un ARN avec une LDC sans recopier les éventuels doublons contenus dans la LDC
 * \param    ldc  La LDC contenant les éléments
 * \param    eval La fonction d'évaluation
 */
ARN ARN_fromLDCSansDoublons(LDC ldc, ARNElementEval eval);

/**
 * \brief    Ajoute les éléments d'une LDC dans un ARN
 */
ARN ARN_insererLDC(ARN arn, LDC ldc);

/**
 * \brief    Ajoute les éléments d'une LDC dans un ARN, sans doublons
 */
ARN ARN_insererLDCSansDoublons(ARN arn, LDC ldc);

# endif
