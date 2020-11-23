#include "HTTPRequest.h"

#include <iostream>
#include <string>

HTTPRequest::HTTPRequest() { this->body = ""; }

void HTTPRequest::setBody(const std::string& body) { this->body += body; }

void HTTPRequest::setMethod(const std::string& method) {
  this->method = method;
}

void HTTPRequest::setResource(const std::string& resource) {
  this->resource = resource;
}

std::string HTTPRequest::getMethod() { return this->method; }

std::string HTTPRequest::getResource() { return this->resource; }

std::string HTTPRequest::getBody() { return this->body; }
