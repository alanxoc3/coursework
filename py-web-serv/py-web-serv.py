#!/usr/bin/env python2
# py-web-serv
# By: Alan Morgan

# A simple python server in Python2.
# Works with images, html, and text!
# If you want to convert it to Python3, you gotta work with byte streams
# and decoding.

from socket import *
import os
import argparse

def main(portNumber):
    CRLF = "\r\n"
    serverPort = portNumber
    serverSocket = socket(AF_INET, SOCK_STREAM)
    serverSocket.bind(('', serverPort))
    serverSocket.listen(1)
    print('The server has started.')

    try:
        while True:
            connectionSocket, addr = serverSocket.accept()
            request = connectionSocket.recv(1024)

            content_type, path, content, ok = requestToFile(request)

            accept_str = "HTTP/1.1 200 OK" + CRLF
            if not ok:
                accept_str = "HTTP/1.1 404 Not Found" + CRLF
            content_prefix = "Content-type: "

            # get request
            connectionSocket.send(accept_str + content_prefix + content_type + CRLF + CRLF + content)
            print("Sent:", (content_type, path))
            connectionSocket.close()

    except KeyboardInterrupt:
        print("\nClosing server. Goodbye.")
        serverSocket.close()

def requestToFile(request):
    path = None

    html_template = "<HTML><HEAD><TITLE>%s</TITLE></HEAD><BODY>%s</BODY></HTML>"
    error = ("text/html", path, html_template % ("Server Request Error", "There was a problem with the server request you sent. Was it correct? This webserver only works with \"HTTP 1.1\"."), False)

    line_list = request.split('\r\n')
    if len(line_list) < 1:
        return error
    
    name_list = line_list[0].split()
    if len(name_list) != 3 or name_list[0].upper() != 'GET' or name_list[2].upper() != "HTTP/1.1":
        return error

    perm_error = ("text/html", path, html_template % ("Permission Denied", "You are trying to break this server, aren't you? Well, I won't let you!"), False)
    path = "./" + name_list[1]

    # Make sure they don't break the rules.
    relativePath = os.path.relpath(path)
    if relativePath.startswith(".."):
        return perm_error

    if relativePath == ".":
        relativePath = "index.html"

    path = "static/" + relativePath

    # Open the file, index.html is opened if the file doesn't exist.
    notf_error = ("text/html", path, html_template % ("Not Found", "Sorry, the file you were looking for was not found."), False)
    file_content = None
    try:
        with open(path, 'r') as myfile:
            file_content=myfile.read()
    except IOError:
        return notf_error

    # Now my mimes. Mr. Mime!
    mime = filenameToMime(path)

    return (mime, path, file_content, True)

def filenameToMime(filename):
    def file_end(x):
        return filename.endswith(x)

    if file_end(".htm") or file_end(".html"):
        return "text/html"
    elif file_end(".gif"):
        return "image/gif"
    elif file_end(".png"):
        return "image/png"
    elif file_end(".jpg") or file_end(".jpeg"):
        return "image/jpeg"
    elif file_end(".txt"):
        return "text/plain"
    elif file_end(".txt") or file_end(".jpeg"):
        return "text/plain"
    return "application/octet-stream"

if __name__ == "__main__":
    # create a parser object
    parser = argparse.ArgumentParser(prog="py-web-serv",description = "A simple python web server.")

    # arguments
    parser.add_argument("port", type=int, help="The port to run your server on.")

    # parse it
    args = parser.parse_args()

    # run the code!
    main(args.port)
