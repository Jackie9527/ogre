#include "OgreStableHeaders.h"

namespace Ogre{
    //-----------------------------------------------------------------------
    const String &HAPZipArchiveFactory::getType() const
    {
        static String type = "HAPZip";
        return type;
    }
    //-----------------------------------------------------------------------
    Archive *HAPZipArchiveFactory::createInstance( const String& name, bool readOnly )
    {
#if 0
        String apkName = name;
        if (apkName.size() > 0 && apkName[0] == '/')
            apkName.erase(apkName.begin());

        AAsset* asset = AAssetManager_open(mAssetMgr, apkName.c_str(), AASSET_MODE_BUFFER);
        if(asset)
        {
            EmbeddedZipArchiveFactory::addEmbbeddedFile(apkName, (const Ogre::uint8*)AAsset_getBuffer(asset), AAsset_getLength(asset), 0);
            mOpenAssets.emplace(apkName, asset);
        }

        return EmbeddedZipArchiveFactory::createInstance(apkName, readOnly);
#endif
        return nullptr;
    }
    void HAPZipArchiveFactory::destroyInstance(Archive* ptr)
    {
#if 0
        AAsset_close(mOpenAssets[ptr->getName()]);
        EmbeddedZipArchiveFactory::destroyInstance(ptr);
#endif
    }
}
