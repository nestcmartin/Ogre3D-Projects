#include "OgreFileSystemLayer.h"
#include "OgreConfigFile.h"
#include "OgreResourceGroupManager.h"
#include "OgreRoot.h"
#include "OgrePlugin.h"
#include "OgreGpuProgramManager.h"

#include "Graphics.h"
#include "ResourcesManager.h"

Ogre::FileSystemLayer* ResourcesManager::FSLayer = nullptr;

void ResourcesManager::Init()
{
	FSLayer = new Ogre::FileSystemLayer("Ogre");
    Locate();
    Load();
}

void ResourcesManager::Locate()
{
    Ogre::ConfigFile cf;
    Ogre::String resourcesPath = FSLayer->getConfigFilePath("resources.cfg");
    cf.load(resourcesPath);

    Ogre::String sec, type, arch;
    Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();

    // Go through all specified resource groups
    Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
    for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci)
    {
        sec = seci->first;
        const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
        Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

        // Go through all resource paths
        for (i = settings.begin(); i != settings.end(); i++)
        {
            type = i->first;
            arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
            rgm.addResourceLocation(arch, type, sec);
        }
    }

    sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
    const Ogre::ResourceGroupManager::LocationList genLocs = rgm.getResourceLocationList(sec);
    OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

    arch = genLocs.front().archive->getName();
    arch = Ogre::StringUtil::replaceAll(arch, "Media/../../Tests/Media", "");
    arch = Ogre::StringUtil::replaceAll(arch, "media/../../Tests/Media", "");
    type = genLocs.front().archive->getType();

    bool hasCgPlugin = false;
    const Ogre::Root::PluginInstanceList& plugins = Graphics::GetRoot()->getInstalledPlugins();
    for (size_t i = 0; i < plugins.size(); i++)
    {
        if (plugins[i]->getName() == "Cg Program Manager")
        {
            hasCgPlugin = true;
            break;
        }
    }

    bool use_HLSL_Cg_shared = hasCgPlugin || Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl");

    // Add locations for supported shader languages
    if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
    {
        rgm.addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
        rgm.addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
    }
    else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
    {
        rgm.addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
        rgm.addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

        if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
        {
            rgm.addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
        }
        if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
        {
            rgm.addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
        }
    }
    else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
    {
        rgm.addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
    }

    if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("spirv"))
    {
        rgm.addResourceLocation(arch + "/materials/programs/SPIRV", type, sec);
    }

    if (hasCgPlugin)
        rgm.addResourceLocation(arch + "/materials/programs/Cg", type, sec);
    if (use_HLSL_Cg_shared)
        rgm.addResourceLocation(arch + "/materials/programs/HLSL_Cg", type, sec);
}

void ResourcesManager::Load()
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void ResourcesManager::Unload()
{
    for (auto& it : Ogre::ResourceGroupManager::getSingleton().getResourceManagers())
    {
        it.second->unloadUnreferencedResources();
    }
}

void ResourcesManager::Release()
{
	if (FSLayer)
	{
		delete FSLayer;
		FSLayer = nullptr;
	}
}