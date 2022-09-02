#pragma once

#include <exception>
#include <string>

class RepositoryException : public std::exception {

private:
    std::string message;

public:

    /// <summary>
    /// Constructor for RepositoryException class
    /// </summary>
    /// <param name="message">nessage of the exception</param>
    RepositoryException(std::string message) : message{ message } {};

    /// <summary>
    /// Returns the message of the exception
    /// </summary>
    std::string what() { return this->message; };
};

class ValidatorException : public std::exception {

private:
    std::string message;

public:

    /// <summary>
    /// Constructor for ValidatorException class
    /// </summary>
    /// <param name="message">nessage of the exception</param>
    ValidatorException(std::string message) : message{ message } {};

    /// <summary>
    /// Returns the message of the exception
    /// </summary>
    std::string what() { return this->message; };
};

class UserInputException : public std::exception {

private:
    std::string message;

public:

    /// <summary>
    /// Constructor for UserInputException class
    /// </summary>
    /// <param name="message">nessage of the exception</param>
    UserInputException(std::string message) : message{ message } {};

    /// <summary>
    /// Returns the message of the exception
    /// </summary>
    std::string what() { return this->message; };
};

class FileException : public std::exception {

private:
    std::string message;

public:

    /// <summary>
    /// Constructor for FileException class
    /// </summary>
    /// <param name="message">nessage of the exception</param>
    FileException(std::string message) : message{ message } {};

    /// <summary>
    /// Returns the message of the exception
    /// </summary>
    std::string what() { return this->message; };
};

class UndoRedoException : public std::exception {

private:
    std::string message;

public:

    /// <summary>
    /// Constructor for UndoRedoException class
    /// </summary>
    /// <param name="message">nessage of the exception</param>
    UndoRedoException(std::string message) : message{ message } {};

    /// <summary>
    /// Returns the message of the exception
    /// </summary>
    std::string what() { return this->message; };
};