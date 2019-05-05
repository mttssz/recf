#include "CFileOperation.h"

CFileOperation::CFileOperation (const std::string& t_source_dir, const std::string& t_target_dir, std::string& t_patterns) :
    m_source_dir(t_source_dir), m_target_dir(t_target_dir)
{
    // if the patterns contain uppercase characters, it is considered as case sensitive
    m_case_sensitive_regex = !std::all_of (t_patterns.begin (), t_patterns.end (), islower);

    // sanitize patterns for the regex conversion
    replace_all (t_patterns, ".", "\\.");
    replace_all (t_patterns, "?", ".");
    replace_all (t_patterns, "*", ".*");

    // split the patterns into parts by every comma
    split (t_patterns, ',', std::back_inserter (m_patterns));
}

CFileOperation::~CFileOperation ()
{ }

void CFileOperation::replace_all (std::string& t_s, const std::string& t_from, const std::string& t_to)
{
    // starting position
    size_t index = 0;

    // unti we reach the end of the string
    while (true)
    {
        // find the substring index starting from the position
        index = t_s.find (t_from, index);

        // if we didn't find it
        if (index == std::string::npos) break;

        // replace n characters starting from the position to the new string
        t_s.replace (index, t_from.length (), t_to);

        // adjust the position
        index += t_to.length ();
    }
}

void CFileOperation::initialize ()
{
    // loop over everything starting from the source directory recursively
    for (std::filesystem::recursive_directory_iterator it (m_source_dir), end; it != end; ++it)
    {
        // if it's not a directory
        if (!std::filesystem::is_directory (it->path ()))
        {
            // check it against every pattern
            for (size_t i = 0; i < m_patterns.size (); i++)
            {
                // try to make it into a regex
                std::regex e;
                try 
                {
                    // if we want a case sensitive regex do it with the default options
                    if (m_case_sensitive_regex)
                        e = std::regex (m_patterns[i]);
                    // else specify case insensitivity
                    else
                        e = std::regex (m_patterns[i], std::regex::flag_type::icase);
                }
                catch (const std::regex_error & ex)
                {
                    // output the error
                    std::cout << ex.what ();
                }

                // get only the filename from the path
                std::string file_name = it->path ().filename ().string ();
                
                // if it matches this regex
                if (std::regex_match (file_name, e))
                { 
                    // push it to the vector then step out
                    m_files_in_dir.push_back (it->path ());
                    break;
                }
            }
        }
    }

    try
    {
        // try to make sure the target directory path exists
        std::filesystem::create_directories (m_target_dir);
    }
    catch (const std::filesystem::filesystem_error& ex)
    {
        // output the error
        std::cout << ex.what ();
    }
}
