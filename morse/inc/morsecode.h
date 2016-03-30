/* struct define */
typedef struct morsecode
{
	struct morsecode *next;
	unsigned char output;
	unsigned char morse_mask[6];
} morsecode;

/* chain table for decoding*/
__code morsecode letter_a = {&letter_b,'a',{1,2,'\0',1,1,1}};
__code morsecode letter_b = {&letter_c,'b',{2,1,1,1,'\0',1}};
__code morsecode letter_c = {&letter_d,'c',{2,1,2,1,'\0',1}};
__code morsecode letter_d = {&letter_e,'d',{2,1,1,'\0',1,1}};
__code morsecode letter_e = {&letter_f,'e',{1,'\0',1,1,1,1}};
__code morsecode letter_f = {&letter_g,'f',{1,1,2,1,'\0',1}};
__code morsecode letter_g = {&letter_h,'g',{2,2,1,'\0',1,1}};
__code morsecode letter_h = {&letter_i,'h',{1,1,1,1,'\0',1}};
__code morsecode letter_i = {&letter_j,'i',{1,1,'\0',1,1,1}};
__code morsecode letter_j = {&letter_k,'j',{1,2,2,2,'\0',1}};
__code morsecode letter_k = {&letter_l,'k',{2,1,2,'\0',1,1}};
__code morsecode letter_l = {&letter_m,'l',{1,2,1,1,'\0',1}};
__code morsecode letter_m = {&letter_n,'m',{2,2,'\0',1,1,1}};
__code morsecode letter_n = {&letter_o,'n',{2,1,'\0',1,1,1}};
__code morsecode letter_o = {&letter_p,'o',{2,2,2,'\0',1,1}};
__code morsecode letter_p = {&letter_q,'p',{1,2,2,1,'\0',1}};
__code morsecode letter_q = {&letter_r,'q',{2,2,1,2,'\0',1}};
__code morsecode letter_r = {&letter_s,'r',{1,2,1,'\0',1,1}};
__code morsecode letter_s = {&letter_t,'s',{1,1,1,'\0',1,1}};
__code morsecode letter_t = {&letter_u,'t',{2,'\0',1,1,1,1}};
__code morsecode letter_u = {&letter_v,'u',{1,1,2,'\0',1,1}};
__code morsecode letter_v = {&letter_w,'v',{1,1,1,2,'\0',1}};
__code morsecode letter_w = {&letter_x,'w',{1,2,2,'\0',1,1}};
__code morsecode letter_x = {&letter_y,'x',{2,1,1,2,'\0',1}};
__code morsecode letter_y = {&letter_z,'y',{2,1,2,2,'\0',1}};
__code morsecode letter_z = {NULL,'z',{2,2,1,1,'\0',1}};
