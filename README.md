Navigate to the project directory:
$cd ~/mssgque

Compile the project using make
$make

Running the Programs
Run the server in one terminal:
$./server

Run the read process in another terminal:
$./read_process

Run the write process in another terminal:
$./write_process
Run the client in another terminal:
$./client

If make is not available
If you prefer not to use make or encounter further issues, you can manually compile each file using gcc. Here are the commands:

Compile client.c:
$gcc -o client client.c

Compile server.c:
$gcc -o server server.c

Compile read.c:
$gcc -o read_process read.c

Compile write.c:
$gcc -o write_process write.c
