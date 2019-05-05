#pragma once
#include "CFileOperation.h"

class CMoveOperation : public CFileOperation
{
public:
    CMoveOperation (const std::string& sourceDir, const std::string& targetDir, std::string& pattern);
    virtual ~CMoveOperation ();

    virtual int do_operation ();
};

