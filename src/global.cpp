#include "global.h"
#include "log.h"

float durfig(t_figura t){
	if(t == Redonda){
		return 4;
	}else if(t == Blanca){
		return 2;
	}else if(t == Negra){
		return 1;
	}else if(t == Corchea){
		return 0.5;
	}else{
		return 0;
	}
}
