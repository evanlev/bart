
#include <stdbool.h>


#include "misc/cppwrap.h"
#include "misc/types.h"
#include "misc/misc.h"

enum OPT_ARG_TYPE {
	OPT_SPECIAL,
	OPT_SET, OPT_CLEAR,
	OPT_INT, OPT_UINT, OPT_LONG,
	OPT_FLOAT,
	OPT_VEC2, OPT_VEC3,
	OPT_FLOAT_VEC2, OPT_FLOAT_VEC3,
	OPT_STRING,
	OPT_SELECT,
	OPT_SUBOPT,
};

typedef bool opt_conv_f(void* ptr, char c, const char* optarg);

struct opt_s {

	char c;
	const char* s;
	bool arg;
	enum OPT_ARG_TYPE type;
	opt_conv_f* conv;
	void* ptr;
	const char* descr;
};

struct opt_select_s {

	void* ptr;
	const void* value;
	const void* default_value;
	size_t size;
};

struct opt_subopt_s {

	int n;
	struct opt_s* opts;
};

typedef long opt_vec2_t[2];
typedef float opt_fvec2_t[2];
typedef long opt_vec3_t[3];
typedef float opt_fvec3_t[3];

#define OPT_SEL(T, x, v)	&(struct opt_select_s){ (x), &(T){ (v) }, &(T){ *(x) }, sizeof(T) }
#define OPT_SUB(n, opts)	&(struct opt_subopt_s){ (n), (opts) }

#define OPT_SET(c, ptr, descr)			{ (c), NULL, false, OPT_SET, NULL, TYPE_CHECK(bool*, (ptr)), "\t" descr }
#define OPT_CLEAR(c, ptr, descr)		{ (c), NULL, false, OPT_CLEAR, NULL, TYPE_CHECK(bool*, (ptr)), "\t" descr }
#define OPT_ARG(c, type, T, ptr, argname, descr) { (c), NULL, true, type, NULL, TYPE_CHECK(T*, (ptr)), " " argname "      \t" descr }
#define OPT_STRING(c, ptr, argname, descr)	OPT_ARG(c, OPT_STRING, const char*, ptr, argname, descr)
#define OPT_UINT(c, ptr, argname, descr)	OPT_ARG(c, OPT_UINT, unsigned int, ptr, argname, descr)
#define OPT_INT(c, ptr, argname, descr)		OPT_ARG(c, OPT_INT, int, ptr, argname, descr)
#define OPT_LONG(c, ptr, argname, descr)	OPT_ARG(c, OPT_LONG, long, ptr, argname, descr)
#define OPT_FLOAT(c, ptr, argname, descr)	OPT_ARG(c, OPT_FLOAT, float, ptr, argname, descr)
#define OPT_VEC2(c, ptr, argname, descr)	OPT_ARG(c, OPT_VEC2, opt_vec2_t, ptr, argname, descr)
#define OPT_FLVEC2(c, ptr, argname, descr)	OPT_ARG(c, OPT_FLOAT_VEC2, opt_fvec2_t, ptr, argname, descr)
#define OPT_VEC3(c, ptr, argname, descr)	OPT_ARG(c, OPT_VEC3, opt_vec3_t, ptr, argname, descr)
#define OPT_FLVEC3(c, ptr, argname, descr)	OPT_ARG(c, OPT_FLOAT_VEC3, opt_fvec3_t, ptr, argname, descr)
#define OPT_SELECT(c, T, ptr, value, descr)	{ (c), NULL, false, OPT_SELECT, NULL, OPT_SEL(T, TYPE_CHECK(T*, ptr), value), "\t" descr }
#define OPT_SUBOPT(c, argname, descr, NR, opts)	OPT_ARG(c, OPT_SUBOPT, struct opt_subopt_s, OPT_SUB(NR, opts), argname, descr)

// If the character in these macros is 0 (please note: NOT '0'), then it is only a long opt
// Otherwise, it is both
#define OPTL_SET(c, s, ptr, descr)			{ (c), (s), false, OPT_SET, NULL, TYPE_CHECK(bool*, (ptr)), "\t" descr }
#define OPTL_CLEAR(c, s, ptr, descr)			{ (c), (s), false, OPT_CLEAR, NULL, TYPE_CHECK(bool*, (ptr)), "\t" descr }
#define OPTL_ARG(c, s, type, T, ptr, argname, descr) { (c), (s), true, type, NULL, TYPE_CHECK(T*, (ptr)), " " argname "      \t" descr }
#define OPTL_STRING(c, s, ptr, argname, descr)	OPTL_ARG(c, s, OPT_STRING, const char*, ptr, argname, descr)
#define OPTL_UINT(c, s, ptr, argname, descr)	OPTL_ARG(c, s, OPT_UINT, unsigned int, ptr, argname, descr)
#define OPTL_INT(c, s, ptr, argname, descr)	OPTL_ARG(c, s, OPT_INT, int, ptr, argname, descr)
#define OPTL_LONG(c, s, ptr, argname, descr)	OPTL_ARG(c, s, OPT_LONG, long, ptr, argname, descr)
#define OPTL_FLOAT(c, s, ptr, argname, descr)	OPTL_ARG(c, s, OPT_FLOAT, float, ptr, argname, descr)
#define OPTL_VEC2(c, s, ptr, argname, descr)	OPTL_ARG(c, s, OPT_VEC2, opt_vec2_t, ptr, argname, descr)
#define OPTL_FLVEC2(c, s, ptr, argname, descr)	OPTL_ARG(c, s, OPT_FLOAT_VEC2, opt_fvec2_t, ptr, argname, descr)
#define OPTL_VEC3(c, s, ptr, argname, descr)	OPTL_ARG(c, s, OPT_VEC3, opt_vec3_t, ptr, argname, descr)
#define OPTL_FLVEC3(c, s, ptr, argname, descr)	OPTL_ARG(c, s, OPT_FLOAT_VEC3, opt_fvec3_t, ptr, argname, descr)
#define OPTL_SELECT(c, s, T, ptr, value, descr)	{ (c), (s), false, OPT_SELECT, NULL, OPT_SEL(T, TYPE_CHECK(T*, ptr), value), "\t" descr }
#define OPTL_SUBOPT(c, s, argname, descr, NR, opts)	OPTL_ARG(c, s, OPT_SUBOPT, struct opt_subopt_s, OPT_SUB(NR, opts), argname, descr)

extern void cmdline(int* argc, char* argv[], int min_args, int max_args, const char* usage_str, const char* help_str, int n, const struct opt_s opts[n]);

#include "misc/cppwrap.h"

