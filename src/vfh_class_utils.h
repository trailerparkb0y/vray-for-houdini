//
// Copyright (c) 2015-2016, Chaos Software Ltd
//
// V-Ray For Houdini
//
// ACCESSIBLE SOURCE CODE WITHOUT DISTRIBUTION OF MODIFICATION LICENSE
//
// Full license text: https://github.com/ChaosGroup/vray-for-houdini/blob/master/LICENSE
//

#ifndef VRAY_FOR_HOUDINI_CLASS_UTILS_H
#define VRAY_FOR_HOUDINI_CLASS_UTILS_H

#include <OP/OP_Node.h>
#include <UT/UT_Version.h>

namespace VRayForHoudini {

template< typename T >
OP_Node* VFH_VRAY_NODE_CREATOR(OP_Network *parent, const char *name, OP_Operator *entry)
{
	T *t = new T(parent, name, entry);
	// Execute extra initialization
	if (t) {
		t->init();
	}
	return t;
}


#if UT_MAJOR_VERSION_INT >= 16

#define VFH_ADD_OP_OPERATOR(table, OpClass, OpParmTemplate, OpTableName, MinInp, MaxInp, VarList, Flags, InpLabels, MaxOut) \
	OP_Operator *op##OpClass = new OP_Operator( \
		/* Internal name     */ "VRayNode" STRINGIZE(OpClass), \
		/* UI name           */ "V-Ray " STRINGIZE(OpClass), \
		/* Creator           */ VFH_VRAY_NODE_CREATOR<OpClass>, \
		/* Parm templates    */ OpParmTemplate, \
		/* Child table name  */ OpTableName, \
		/* Min # of inputs   */ MinInp, \
		/* Max # of inputs   */ MaxInp, \
		/* Variables list    */ VarList, \
		/* Flags             */ Flags, \
		/* Input labels      */ InpLabels, \
		/* Max # of outputs  */ MaxOut, \
		/* Tab submenu path  */ nullptr \
	); \
	op##OpClass->setIconName("ROP_vray"); \
	table->addOperator(op##OpClass);

#else

#define VFH_ADD_OP_OPERATOR(table, OpClass, OpParmTemplate, OpTableName, MinInp, MaxInp, VarList, Flags, InpLabels, MaxOut) \
	OP_Operator *op##OpClass = new OP_Operator( \
		/* Internal name     */ "VRayNode" STRINGIZE(OpClass), \
		/* UI name           */ "V-Ray " STRINGIZE(OpClass), \
		/* Creator           */ VFH_VRAY_NODE_CREATOR<OpClass>, \
		/* Parm templates    */ OpParmTemplate, \
		/* Min # of inputs   */ MinInp, \
		/* Max # of inputs   */ MaxInp, \
		/* Variables list    */ VarList, \
		/* Flags             */ Flags, \
		/* Input labels      */ InpLabels, \
		/* Max # of outputs  */ MaxOut, \
		/* Tab submenu path  */ nullptr \
	); \
	op##OpClass->setIconName("ROP_vray"); \
	table->addOperator(op##OpClass);

#endif



#define VFH_ADD_OBJ_OPERATOR(table, OpClass) \
	VFH_ADD_OP_OPERATOR(table, OpClass, OpClass::GetPrmTemplate(), SOP_TABLE_NAME, 0u, 1u, nullptr, 0u, nullptr, 1)


#define VFH_ADD_SOP_GENERATOR_CUSTOM(table, OpClass, OpParmTemplate) \
	VFH_ADD_OP_OPERATOR(table, OpClass, OpParmTemplate, nullptr, 0u, 0u, nullptr, OP_FLAG_GENERATOR, nullptr, 1)

#define VFH_ADD_SOP_GENERATOR(table, OpClass) \
	VFH_ADD_SOP_GENERATOR_CUSTOM(table, OpClass, Parm::getPrmTemplate(STRINGIZE(OpClass)))


#if UT_MAJOR_VERSION_INT >= 16

#define VFH_ADD_VOP_OPERATOR(table, OpClass, OpParmTemplate, OpTableName, MinInp, MaxInp, VarList, Flags, MaxOut) \
	VOP_Operator *op##OpClass = new VOP_Operator( \
		/* Internal name     */ "VRayNode" STRINGIZE(OpClass), \
		/* UI name           */ "V-Ray " STRINGIZE(OpClass), \
		/* Creator           */ VFH_VRAY_NODE_CREATOR<OpClass>, \
		/* Parm templates    */ OpParmTemplate, \
		/* Child table name  */ OpTableName, \
		/* Min # of inputs   */ MinInp, \
		/* Max # of inputs   */ MaxInp, \
		/* VOP network mask  */ "VRay", \
		/* Local variables   */ VarList, \
		/* Flags             */ Flags, \
		/* Max # of outputs  */ MaxOut \
	); \
	op##OpClass->setIconName("ROP_vray"); \
	table->addOperator(op##OpClass);

#else

#define VFH_ADD_VOP_OPERATOR(table, OpClass, OpParmTemplate, OpTableName, MinInp, MaxInp, VarList, Flags, MaxOut) \
	VOP_Operator *op##OpClass = new VOP_Operator( \
		/* Internal name     */ "VRayNode" STRINGIZE(OpClass), \
		/* UI name           */ "V-Ray " STRINGIZE(OpClass), \
		/* Creator           */ VFH_VRAY_NODE_CREATOR<OpClass>, \
		/* Parm templates    */ OpParmTemplate, \
		/* Min # of inputs   */ MinInp, \
		/* Max # of inputs   */ MaxInp, \
		/* VOP network mask  */ "VRay", \
		/* Local variables   */ VarList, \
		/* Flags             */ Flags, \
		/* Max # of outputs  */ MaxOut \
	); \
	op##OpClass->setIconName("ROP_vray"); \
	table->addOperator(op##OpClass);

#define VFH_ADD_VOP_OPERATOR_TEST(table, OpClass, OpParmTemplate, OpTableName, MinInp, MaxInp, VarList, Flags, MaxOut) \
	VOP_Operator *op##OpClass = new VOP_Operator( \
		/* Internal name     */ "OUT_Container", \
		/* UI name           */ "OUT_Container" , \
		/* Creator           */ VFH_VRAY_NODE_CREATOR<OpClass>, \
		/* Parm templates    */ OpParmTemplate, \
		/* Min # of inputs   */ MinInp, \
		/* Max # of inputs   */ MaxInp, \
		/* VOP network mask  */ "VRay", \
		/* Local variables   */ VarList, \
		/* Flags             */ Flags, \
		/* Max # of outputs  */ MaxOut \
	);\
	op##OpClass->setIconName("ROP_vray"); \
	table->addOperator(op##OpClass);

#endif

#define VFH_VOP_ADD_OPERATOR_CUSTOM(table, OpPluginType, OpClass, OpParmTemplate, OpFlags) \
	VFH_ADD_VOP_OPERATOR(table, OpClass, OpParmTemplate, nullptr, 0u, VOP_VARIABLE_INOUT_MAX, nullptr, OpFlags, 1u)

#define VFH_VOP_ADD_OPERATOR_CUSTOM_TEST(table, OpPluginType, OpClass, OpParmTemplate, OpFlags) \
	VFH_ADD_VOP_OPERATOR_TEST(table, OpClass, OpParmTemplate, nullptr, 0u, VOP_VARIABLE_INOUT_MAX, nullptr, OpFlags, 1u)

#define VFH_VOP_ADD_OPERATOR(table, OpPluginType, OpClass) \
	VFH_VOP_ADD_OPERATOR_CUSTOM(table, OpPluginType, OpClass, Parm::getPrmTemplate(STRINGIZE(OpClass)), OP_FLAG_UNORDERED)

} // namespace VRayForHoudini

#endif // VRAY_FOR_HOUDINI_CLASS_UTILS_H
