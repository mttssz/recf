#pragma once
#include "CFileOperation.h"

class CCopyOperation : public CFileOperation
{
public:
    CCopyOperation (const std::string& sourceDir, const std::string& targetDir, std::string& pattern);
    virtual ~CCopyOperation ();

    virtual int do_operation ();
};

