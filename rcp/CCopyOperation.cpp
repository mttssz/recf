#include "CCopyOperation.h"

CCopyOperation::CCopyOperation (const std::string& t_source_dir, const std::string& t_target_dir, std::string& t_patterns) :
    CFileOperation (t_source_dir, t_target_dir, t_patterns)
{ }


CCopyOperation::~CCopyOperation ()
{ }

int CCopyOperation::do_operation ()
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
            // try and copy it
            std::filesystem::copy (m_files_in_dir[i], target_file, std::filesystem::copy_options::overwrite_existing);

            // report on the success
            std::cout << m_files_in_dir[i].string() << " copied to " << target_file << " successfully!\n";
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
