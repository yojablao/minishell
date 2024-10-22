// int exice(t_cmd **cmd, int flage, t_shell **data)
// {
//     int original_stdin = -1;
//     int original_stdout = -1;

//     // If there's input redirection
//     if (/* check for input redirection */)
//     {
//         original_stdin = dup(STDIN_FILENO);
//         int fd = open(/* input file */, O_RDONLY);
//         if (fd != -1)
//         {
//             dup2(fd, STDIN_FILENO);
//             close(fd);
//         }
//     }

//     // Execute the command
//     // Your existing execution code here

//     // Restore original file descriptors
//     if (original_stdin != -1)
//     {
//         dup2(original_stdin, STDIN_FILENO);
//         close(original_stdin);
//     }
//     if (original_stdout != -1)
//     {
//         dup2(original_stdout, STDOUT_FILENO);
//         close(original_stdout);
//     }

//     return (0);
// }

// Key changes:

// We backup and restore STDIN_FILENO for each command
// Instead of breaking the loop on EOF, we continue
// We ensure file descriptors are properly restored after each command execution

// Also, make sure in your parsing and execution functions that you're:

// Properly opening and closing redirected files
// Handling file descriptor duplication correctly
// Restoring original file descriptors after command execution

// This should allow the shell to:

// Execute cat < Makefile correctly
// Show the file contents
// Return to the prompt for more commands

// Remember to handle error cases and clean up resources properly. Let me know if you need any clarification or have questions about specific parts of the implementation!
