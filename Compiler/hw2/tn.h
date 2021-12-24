/* tn.h - tokentypes(token 정보), errorTypes(에러 정보) 정의
* programmer - 박기은, 이혜인, 한지수
* date - 27/04/2021
*/

enum tokentypes
{
	TEOF,
	TCONST,
	TELSE,
	TIF,
	TINT,
	TRETURN,
	TVOID,
	TWHILE,
	TADD,
	TSUB,
	TMUL,
	TDIV,
	TMOD,
	TASSIGN,
	TADDASSIGN,
	TSUBASSIGN,
	TMULASSIGN,
	TDIVASSIGN,
	TMODASSIGN,
	TNOT,
	TAND,
	TOR,
	TEQUAL,
	TNOTEQU,
	TLESS,
	TGREAT,
	TLESSE,
	TGREATE,
	TINC,
	TDEC,
	TLSBRACKET,
	TRSBRACKET,
	TLMBRACKET,
	TRMBRACKET,
	TLLBRACKET,
	TRLBRACKET,
	TSQUOTE,
	TBQUOTE,
	TIDENT,
	TNUMBER,
	TFLOAT,
	TSEPARATOR,
	TLINE,
	TERROR,
	TILLID,

	TBRACKET,
	TCOMMA,
	TSEMICOLON,

	TCOMMENT_SINGLE,
	TCOMMENT_MULTI

};

enum errorTypes {
	noerror,
	illsp,
	illid,
	overst,
	overfl,
	illch
};