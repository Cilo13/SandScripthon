#ifndef SANDSCRIPT_H
#define SANDSCRIPT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

//! The possible argument and return types
typedef enum psl_DataType
{
	psl_boolean = 0,
	psl_string = 1,
	psl_integer = 2,
	psl_float = 3,
	psl_ipaddress = 4
} psl_DataType;

//! String arguments and return values are references, not passed by value.
//! Strings are pointer/length (not null-terminated).
typedef struct psl_stringRef
{
	const char*    begin;
	unsigned       length;
} psl_stringRef;

//! The argument and return values, per psl_DataType
typedef union psl_Value
{
	bool          b;     //!< boolean
	struct psl_stringRef s;     //!< string reference
	int64_t       i;     //!< integer
	double        f;     //!< float
	uint8_t       a[16]; //!< address IPv6 or IPv4-mapped-IPv6
} psl_Value;

//! The function signature required for loadable functions.
//! ResultLocation points to where the result will be stored.
//! Arguments points to an array of pointers to the arguments.
//! Null value arguments are represented by null pointers.
//! E.g., if arg0 was defined as float type, first check if it is null by
//!       checking Arguments[0]==0. If it is not null, access the arg by Arguments[0]->f
//! Return value of true indicates the result is valid; false results in a null result.
typedef bool psl_Function(psl_Value* ResultLocation, const psl_Value* const* Arguments);

// Describes one function in the shared library.
typedef struct psl_FunctionDescription
{
	const char*   functionName;   //!< null-terminated string for the name of the function in policy.
	uint32_t      flags;          //!< Flags. See psl_Flag_* Set unused bits to to 0.
	psl_Function* functionPointer;//!< Function to be called at each invocation.
	psl_DataType  returnType;     //!< Data type of the function return value.
	uint16_t      numArgs;        //!< Number of arguments the function requires.
	const psl_DataType* argTypes; //!< Data types of each function argument.
} psl_FunctionDescription;

// include this flag in the flags field if the function depends solely on its inputs.
// If this flag is set, some optimizations may occur.
#define psl_Flag_Pure  (0x00000001)

typedef struct psl_Manifest
{
	//! Library API version identifier. Use 1.
	unsigned                       version;
	//! Number of entries in the functionDescriptions array.
	unsigned                       numFunctionDescriptions;
	//! Array, with one entry for each function in the shared library.
	const psl_FunctionDescription* const* functionDescriptions;
} psl_Manifest;

//! Function signature required for the function named "GetManifest"
typedef const psl_Manifest* psl_GetManifest();

//! The function name to be retrieved via dlsym() from the shared library.
//! This is the version 1 name. Different versions should implement different names.
//! A shared library could implement multiple versions.
#define psl_GetManifestFunctionNameV1 "GetManifest"

// handle for an instance of an event allocated and freed by shared lib.
typedef void* psl_EventInstanceHandle;

//! @param context      Provides the context number of the event that is returned.
//! @param eventHandle  Returns a handle to the memory holding an event.
//! @return -1 if no events; otherwise the number of events waiting after this one.
typedef int psl_PollEventsFn(unsigned context, psl_EventInstanceHandle* eventHandle);

typedef void psl_FreeEventFn(psl_EventInstanceHandle eventHandle);

typedef struct psl_EventDescription
{
	const char*  eventName;     // what the event should be called in error logs, PDB, etc.
	unsigned     contextNumber;  // start numbering at 1.
	// the function to call to see what events need to be run
	psl_PollEventsFn* pollEvents;
	// function to call to free an event handle
	psl_FreeEventFn*   freeEvent;
} psl_EventDescription;

//! @param ResultLocation  Place the result here, of type type indicated in psl_EventField
//! @param eventHandle     Points to the memory of the event that fired. Must not be used if the field is a constant.
//! @return false if null, true otherwise (and result is provided)
typedef bool psl_FieldGetFn(psl_Value* ResultLocation, psl_EventInstanceHandle eventHandle);

typedef struct psl_EventField
{
	unsigned contextNumber; // what context the field applies to
	const char* fieldName;  // full name of field, such as MyEvent.foo
	psl_DataType  type;     // is it string, float, etc.?
	uint32_t      flags;    // isConstant, canOptimize, etc. TBD.
	psl_FieldGetFn*  getFunction;  // call to obtain the field from the event pointed by handle.
} psl_EventField;

typedef struct psl_EventManifest
{
	unsigned version;
	unsigned numDescriptions;
	unsigned numFields;
	const psl_EventDescription* const* eventDescriptions;
	const psl_EventField* const* eventFields;
} psl_EventManifest;

typedef const psl_EventManifest* psl_GetEventManifest();

//! The function name to be retrieved via dlsym() from the shared library.
#define psl_GetEventManifestFunctionNameV1 "GetEventManifest"
#ifdef __cplusplus
} // end extern "C"
#endif

#endif
