//
// Copyright (c) 2015-2016, Chaos Software Ltd
//
// V-Ray For Houdini
//
// ACCESSIBLE SOURCE CODE WITHOUT DISTRIBUTION OF MODIFICATION LICENSE
//
// Full license text: https://github.com/ChaosGroup/vray-for-houdini/blob/master/LICENSE
//

#ifdef  CGR_HAS_AUR
#ifndef VRAY_FOR_HOUDINI_SOP_NODE_PHOENIX_CACHE_H
#define VRAY_FOR_HOUDINI_SOP_NODE_PHOENIX_CACHE_H

#include "sop_node_base.h"
#include <string>
#include <vector>

namespace VRayForHoudini {
namespace SOP {


struct FluidFrame
{
	FluidFrame():
		data(nullptr)
	{
		size[0] = 0;
		size[1] = 0;
		size[2] = 0;
	}

	~FluidFrame() {
		FreePtrArr(data);
	}

	float             *data;
	int                size[3];
	VUtils::Transform  c2n;
};


class FluidCache
{
	typedef VUtils::HashMap<FluidFrame> FluidFrames;

public:
	FluidFrame  *getData(const char *filePath, const int fluidResample=32);

private:
	FluidFrames  m_frames;

};


class PhxShaderCache:
		public SOP::NodeBase
{
public:
	static PRM_Template      *GetPrmTemplate();

public:
	PhxShaderCache(OP_Network *parent, const char *name, OP_Operator *entry):NodeBase(parent, name, entry) {}
	virtual                  ~PhxShaderCache() {}

	virtual OP_NodeFlags     &flags() VRAY_OVERRIDE;
	virtual OP_ERROR          cookMySop(OP_Context &context) VRAY_OVERRIDE;
	virtual PluginResult      asPluginDesc(Attrs::PluginDesc &pluginDesc, VRayExporter &exporter, ExportContext *parentContext=nullptr) VRAY_OVERRIDE;

protected:
	virtual void              setPluginType() VRAY_OVERRIDE;

private:
	static FluidCache         FluidFiles;
	std::vector<std::string>  m_ChannelNames;

	// ui dropdowns will point to this
	// causing reallocations here will invalidate pointer in UI and cause crashes
	// every time this is changed remove all references from UI
	// will be colon separated list to be parsed on ui load
	std::string               m_ChannelNamesSerialized;
};

} // namespace SOP
} // namespace VRayForHoudini

#endif // VRAY_FOR_HOUDINI_SOP_NODE_PHOENIX_CACHE_H
#endif // CGR_HAS_AUR
