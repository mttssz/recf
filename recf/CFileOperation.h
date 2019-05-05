#pragma once

class CFileOperation
{
private:
    bool m_case_sensitive_regex;

    // method to split string by a delimiter
    template<typename Out>
    void split (const std::string& t_s, char t_delim, Out t_result)
    {
        // get the string into a stringstream
        std::stringstream ss (t_s);
        std::string item;

        // while getline returns a new item
        while (std::getline (ss, item, t_delim))
        {
            // push it to the output 
            *(t_result++) = item;
        }
    }

    // method to replace all occurences of a substring to another
    void replace_all (std::string& s, const std::string& from, const std::string& to);
protected:
    std::string                         m_source_dir;    // where to walk starts from
    std::string                         m_target_dir;    // the target directory for the files
    std::vector<std::string>            m_patterns;     // the patterns we're looking for
    std::vector<std::filesystem::path>  m_files_in_dir;   // all the files in the directory and its subdirectories

    // method to initialize the operation with the needed files
    void initialize ();
public:
    CFileOperation (const std::string& sourceDir, const std::string& targetDir, std::string& pattern);
    virtual ~CFileOperation ();
    virtual int do_operation () = 0;
};

