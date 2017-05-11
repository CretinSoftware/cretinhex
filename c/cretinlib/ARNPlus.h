

# ifndef __CRETINLIB_ARNPLUS__
# define __CRETINLIB_ARNPLUS__

# include "ARN.h"
# include "LDC.h"



LDC ARN_lister(ARN arn);

ARN ARN_fromLDC(LDC ldc, ARNElementEval eval);
ARN ARN_fromLDCSansDoublons(LDC ldc, ARNElementEval eval);
ARN ARN_insererLDC(ARN arn, LDC ldc);
ARN ARN_insererLDCSansDoublons(ARN arn, LDC ldc);

# endif
