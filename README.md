# recf
Console tool to recursively move or copy files from a directory matching a specified criteria.

---

# Usage:

To use the tool use the following:
<pre><b>recf</b> operation "patterns" target_dir [source_dir]</pre>

#### Operations:
<pre>m - move files matching the pattern
c - copy files matching the pattern
h - display the help text</pre>

#### Patterns:
The patterns part of the command should be a comma-delimited list of patterns surrounded by quotes. Wildcards like ? and * are supported. If either pattern contains an uppercase character, the whole thing becomes case sensitive.

Example:
<pre>"*.png"		- matches every file with the extension png
"a*.png"	- matches every file that starts with an a and is a png
"A*.jpg		- matches every file that starts with an <b>uppercase</b> A and is a png
"*.png,*.jpeg"	- matches every png or jpeg file</pre>

#### Target directory:
Where the files matching the pattern should be copied to. If the path does not exist, the tool attempts to create it.

#### Source directory:
Where the recursive walking should start from. This is an optional parameter and defaults to the current working directory.

# Return codes:
The tool returns with exit codes based on the result of the process.

| Code name            | Code value | Code description                                  |
|----------------------|------------|---------------------------------------------------|
| SUCCESS              | 0          | The tool finished successfully.                   |
| NOT_ENOUGH_ARGUMENTS | 10         | Not enough arguments were provided.               |
| INVALID_ARGUMENTS    | 11         | Some arguments provided were invalid.             |
| FILESYSTEM_ERROR     | 12         | A filesystem error occurred during the operation. |