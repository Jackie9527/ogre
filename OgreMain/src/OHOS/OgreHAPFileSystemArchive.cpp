#include "OgreStableHeaders.h"



namespace Ogre{
namespace {
    class HAPFileSystemArchive : public Archive
    {
    private:
        
        String mPathPreFix;

    public:
        HAPFileSystemArchive(const String& name, const String& archType);
        ~HAPFileSystemArchive();

        /// @copydoc Archive::isCaseSensitive
        bool isCaseSensitive(void) const override;

        /// @copydoc Archive::load
        void load() override;
        /// @copydoc Archive::unload
        void unload() override;

        /// @copydoc Archive::open
        DataStreamPtr open(const String& filename, bool readOnly = true) const override;

        /// @copydoc Archive::create
        DataStreamPtr create(const String& filename) override;

        /// @copydoc Archive::remove
        void remove(const String& filename) override;

        /// @copydoc Archive::list
        StringVectorPtr list(bool recursive = true, bool dirs = false) const override;

        /// @copydoc Archive::listFileInfo
        FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false) const override;

        /// @copydoc Archive::find
        StringVectorPtr find(const String& pattern, bool recursive = true, bool dirs = false) const override;

        /// @copydoc Archive::findFileInfo
        FileInfoListPtr findFileInfo(const String& pattern, bool recursive = true, bool dirs = false) const override;

        /// @copydoc Archive::exists
        bool exists(const String& filename) const override;

        /// @copydoc Archive::getModifiedTime
        time_t getModifiedTime(const String& filename) const override;
    };

	std::map<String, std::vector< String > > mFiles;
#if 0
	bool IsFolderParsed( const String& Folder ) {
		bool parsed = false;
		std::map<String, std::vector< String > >::iterator iter = mFiles.find( Folder );
		if(iter != mFiles.end()) parsed = true;
		return parsed;
	}

	void ParseFolder( AAssetManager* AssetMgr, const String& Folder ) {

		std::vector<String> mFilenames;
		AAssetDir* dir = AAssetManager_openDir(AssetMgr, Folder.c_str());
		const char* fileName = NULL;
		while((fileName = AAssetDir_getNextFileName(dir)) != NULL) {
			mFilenames.push_back( String( fileName ) );
		}
		mFiles.insert( std::make_pair( Folder, mFilenames ) );
	}
#endif
}
	HAPFileSystemArchive::HAPFileSystemArchive(const String& name, const String& archType)
		:Archive(name, archType)
	{
#if 0
		if (mName.size() > 0 && mName[0] == '/')
			mName.erase(mName.begin());

		mPathPreFix = mName;
		if (mPathPreFix.size() > 0)
			mPathPreFix += "/";
			
		if(!IsFolderParsed( mName )) {
			ParseFolder( mAssetMgr, mName );
		}		
#endif	
	}

	HAPFileSystemArchive::~HAPFileSystemArchive()
	{
		std::map<String, std::vector< String > >::iterator iter = mFiles.find( mName );
		if (iter != mFiles.end()) {
			iter->second.clear();
			mFiles.erase( iter );
		}
		unload();
	}

	bool HAPFileSystemArchive::isCaseSensitive() const
	{
		return true;
	}

	void HAPFileSystemArchive::load()
	{

	}

	void HAPFileSystemArchive::unload()
	{

	}

	DataStreamPtr HAPFileSystemArchive::open(const Ogre::String &filename, bool readOnly) const
	{
#if 0
	    MemoryDataStreamPtr stream;
		AAsset* asset = AAssetManager_open(mAssetMgr, (mPathPreFix + filename).c_str(), AASSET_MODE_BUFFER);
		if(asset)
		{
			off_t length = AAsset_getLength(asset);
            stream = std::make_shared<MemoryDataStream>(filename, length, true, true);
			memcpy(stream->getPtr(), AAsset_getBuffer(asset), length);
			AAsset_close(asset);
		}
		return stream;
#endif
		return nullptr;
	}

	DataStreamPtr HAPFileSystemArchive::create(const Ogre::String &filename)
	{
		return DataStreamPtr();
	}

	void HAPFileSystemArchive::remove(const String &filename)
	{

	}

	StringVectorPtr HAPFileSystemArchive::list(bool recursive, bool dirs) const
	{
		StringVectorPtr files(new StringVector);
		std::map<String, std::vector< String > >::iterator iter = mFiles.find( mName );
		std::vector< String > fileList = iter->second;
		for( size_t i = 0; i < fileList.size(); i++ )
		{
			files->push_back(fileList[i]);
		}
		return files;
	}

	FileInfoListPtr HAPFileSystemArchive::listFileInfo(bool recursive, bool dirs) const
	{
		FileInfoListPtr files(new FileInfoList);
#if 0
		std::map<String, std::vector< String > >::iterator iter = mFiles.find( mName );
		std::vector< String > fileList = iter->second;
		for( size_t i = 0; i < fileList.size(); i++ )
		{
			AAsset* asset = AAssetManager_open(mAssetMgr, (mPathPreFix + fileList[i]).c_str(), AASSET_MODE_UNKNOWN);
			if(asset)
			{
				FileInfo info;
				info.archive = this;
				info.filename = fileList[i];
				info.path = mName;
				info.basename = fileList[i];
				info.compressedSize = AAsset_getLength(asset);
				info.uncompressedSize = info.compressedSize;
				files->push_back(info);
				AAsset_close(asset);
			}
		}
#endif
		return files;
	}

	StringVectorPtr HAPFileSystemArchive::find(const String& pattern, bool recursive, bool dirs) const
	{
		StringVectorPtr files(new StringVector);
		std::map<String, std::vector< String > >::iterator iter = mFiles.find( mName );
		std::vector< String > fileList = iter->second;
		for( size_t i = 0; i < fileList.size(); i++ ) 
		{
			if(StringUtil::match(fileList[i], pattern))
				files->push_back(fileList[i]);
		}
		return files;
	}

	FileInfoListPtr HAPFileSystemArchive::findFileInfo(const String& pattern, bool recursive, bool dirs) const
	{
		FileInfoListPtr files(new FileInfoList);
#if 0
		std::map<String, std::vector< String > >::iterator iter = mFiles.find( mName );
		std::vector< String > fileList = iter->second;
		for( size_t i = 0; i < fileList.size(); i++ ) 
		{
			if(StringUtil::match(fileList[i], pattern)) 
			{
				AAsset* asset = AAssetManager_open(mAssetMgr, (mPathPreFix + fileList[i]).c_str(), AASSET_MODE_UNKNOWN);
				if(asset) {
					FileInfo info;
					info.archive = this;
					info.filename = fileList[i];
					info.path = mName;
					info.basename = fileList[i];
					info.compressedSize = AAsset_getLength(asset);
					info.uncompressedSize = info.compressedSize;
					files->push_back(info);
					AAsset_close(asset);
				}
			}
		}
#endif
		return files;
	}

	bool HAPFileSystemArchive::exists(const String& filename) const
	{
#if 0
		AAsset* asset = AAssetManager_open(mAssetMgr, (mPathPreFix + filename).c_str(), AASSET_MODE_UNKNOWN);
		if(asset)
		{
			AAsset_close(asset);
			return true;
		}
#endif
		return false;
	}

	time_t HAPFileSystemArchive::getModifiedTime(const Ogre::String &filename) const
	{
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////////

	const String &HAPFileSystemArchiveFactory::getType() const
	{
		static String type = "HAPFileSystem";
		return type;
	}

    Archive *HAPFileSystemArchiveFactory::createInstance( const String& name, bool readOnly )
    {
        return OGRE_NEW HAPFileSystemArchive(name, getType());
    }
}
