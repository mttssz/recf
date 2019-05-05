#include "CMoveOperation.h"

CMoveOperation::CMoveOperation (const std::string& t_source_dir, const std::string& t_target_dir, std::string& t_patterns) :
    CFileOperation (t_source_dir, t_target_dir, t_patterns)
{ }


CMoveOperation::~CMoveOperation ()
{ }

int CMoveOperation::do_operation ()
{
    // do the init
    initialize ();

    // loop over the files
    for (size_t i = 0; i < m_files_in_dir.size (); i++)
    {
        // build the target filepath
        std::string target_file = m_target_dir + "\\" + m_files_in_dir[i].filename ().string ();

        try
        {
            // try and move it
            std::filesystem::rename (m_files_in_dir[i], target_file);

            // report on the success
            std::cout << m_files_in_dir[i].string() << " moved to " << target_file << " successfully!\n";
        }
        catch (const std::filesystem::filesystem_error & ex)
        {
            // log the error
            std::cout << ex.what ();

            // return an error code
            return error_code::FILESYSTEM_ERROR;
        }
    }

    // done
    return error_code::SUCCESS;
}
