#include "DataDirEntryWrapper.h"
#include "PEFile.h"

using namespace pe;

//-------------
pe::IMAGE_DATA_DIRECTORY* DataDirEntryWrapper::getDataDirectory()
{
    PEFile *pe = dynamic_cast<PEFile*> (m_Exe);
    if (pe == NULL) return NULL;

    IMAGE_DATA_DIRECTORY *d = pe->getDataDirectory();
    return d;
}

offset_t DataDirEntryWrapper::getDirEntryAddress()
{
    if (this->entryType >= pe::DIR_ENTRIES_COUNT) return INVALID_ADDR;

    IMAGE_DATA_DIRECTORY *d = getDataDirectory();
    if (!d) return INVALID_ADDR;

    offset_t rva = static_cast<offset_t>(d[this->entryType].VirtualAddress);
    if (rva == 0) return INVALID_ADDR;
    return rva;
}

bufsize_t DataDirEntryWrapper::getDirEntrySize()
{
    if (this->entryType >= pe::DIR_ENTRIES_COUNT) return 0;

    IMAGE_DATA_DIRECTORY *d = getDataDirectory();
    if (!d) return 0;

    bufsize_t size = static_cast<bufsize_t>(d[this->entryType].Size);
    return size;
}
