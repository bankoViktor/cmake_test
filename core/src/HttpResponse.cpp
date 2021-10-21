#include "../include/HttpResponse.h"
#include "../include/Utils.h"


HttpResponse::HttpResponse(const HttpRequest& request)
{
	m_pRequest = &request;
	m_pBody = nullptr;
	m_nStatusCode = (unsigned int)HttpStatusCodes::OK;
	m_psConentType = new std::string();
}

HttpResponse::~HttpResponse()
{
	SafeReleasePonter(m_pBody);
	SafeReleasePonter(m_psConentType);
}

void HttpResponse::Write(const char* content, const char* conentType)
{
	// Body
	SafeReleasePonter(m_pBody);
	size_t len = strlen(content) + 1;
	m_pBody = new char[len];
	strcpy_s((char*)m_pBody, len, content);

	// content type
	*m_psConentType = conentType;
}

void HttpResponse::Write(const std::string& content, const std::string& conentType)
{
	Write(content.c_str(), conentType.c_str());
}

void HttpResponse::SetStatusCode(HttpStatusCodes statusCode)
{
	m_nStatusCode = (unsigned int)statusCode;
}

void HttpResponse::SetStatusCode(unsigned int statusCode)
{
	m_nStatusCode = statusCode;
}

unsigned int HttpResponse::GetStatusCode() const
{
	return m_nStatusCode;
}

const HttpRequest* HttpResponse::GetRequest() const
{
	return m_pRequest;
}

const char* HttpResponse::TranslateStatusCode(HttpStatusCodes status)
{
	switch (status)
	{
	// 1xx Informational 
	case HttpStatusCodes::Continue:							return "Continue";
	case HttpStatusCodes::SwitchingProtocols:				return "Switchin gProtocols";
	case HttpStatusCodes::Processing:						return "Processing";
	case HttpStatusCodes::EarlyHints:						return "Early Hints";
	
	// 2xx Success
	case HttpStatusCodes::OK:								return "OK";
	case HttpStatusCodes::Created:							return "Created";
	case HttpStatusCodes::Accepted:							return "Accepted";
	case HttpStatusCodes::NonAuthoritativeInformation:		return "Non Authoritative Information";
	case HttpStatusCodes::NoContent:						return "No Content";
	case HttpStatusCodes::ResetContent:						return "Reset Content";
	case HttpStatusCodes::PartialContent:					return "Partial Content";
	case HttpStatusCodes::MultiStatus:						return "Multi Status";
	case HttpStatusCodes::AlreadyReported:					return "Already Reported";
	case HttpStatusCodes::IMUsed:							return "IM Used";
	
	// 3xx Redirection
	case HttpStatusCodes::MultipleChoices:					return "Multiple Choices";
	case HttpStatusCodes::MovedPermanently:					return "Moved Permanently";
	case HttpStatusCodes::Found:							return "Found";
	case HttpStatusCodes::SeeOther:							return "See Other";
	case HttpStatusCodes::NotModified:						return "Not Modified";
	case HttpStatusCodes::UseProxy:							return "Use Proxy";
	case HttpStatusCodes::SwitchProxy:						return "Switch Proxy";
	case HttpStatusCodes::TemporaryRedirect:				return "Temporary Redirect";
	case HttpStatusCodes::PermanentRedirect:				return "Permanent Redirect";

	// 4xx Client Errors
	case HttpStatusCodes::BadRequest:						return "Bad Request";
	case HttpStatusCodes::Unauthorized:						return "Unauthorized";
	case HttpStatusCodes::PaymentRequired:					return "Payment Required";
	case HttpStatusCodes::Forbidden:						return "Forbidden";
	case HttpStatusCodes::NotFound:							return "Not Found";
	case HttpStatusCodes::MethodNotAllowed:					return "Method Not Allowed";
	case HttpStatusCodes::NotAcceptable:					return "Not Acceptable";
	case HttpStatusCodes::ProxyAuthenticationRequired:		return "Proxy Authentication Required";
	case HttpStatusCodes::RequestTimeout:					return "Request Timeout";
	case HttpStatusCodes::Conflict:							return "Conflict";
	case HttpStatusCodes::Gone:								return "Gone";
	case HttpStatusCodes::LengthRequired:					return "Length Required";
	case HttpStatusCodes::PreconditionFailed:				return "Precondition Failed";
	case HttpStatusCodes::PayloadTooLarge:					return "Payload Too Large";
	case HttpStatusCodes::URITooLong:						return "URI Too Long";
	case HttpStatusCodes::UnsupportedMediaType:				return "Unsupported Media Type";
	case HttpStatusCodes::RangeNotSatisfiable:				return "Range Not Satisfiable";
	case HttpStatusCodes::ExpectationFailed:				return "Expectation Failed";
	case HttpStatusCodes::IAmTeapot	:						return "I'm Teapot";
	case HttpStatusCodes::MisdirectedRequest:				return "Misdirected Request";
	case HttpStatusCodes::UnprocessableEntity:				return "Unprocessable Entity";
	case HttpStatusCodes::Locked:							return "Locked";
	case HttpStatusCodes::FailedDependency:					return "Failed Dependency";
	case HttpStatusCodes::TooEarly:							return "Too Early";
	case HttpStatusCodes::UpgradeRequired:					return "Upgrade Required";
	case HttpStatusCodes::PreconditionRequired:				return "Precondition Required";
	case HttpStatusCodes::TooManyRequests:					return "Too Many Requests";
	case HttpStatusCodes::RequestHeaderFieldsTooLarge:		return "Request Header Fields Too Large";
	case HttpStatusCodes::UnavailableForLegalReasons:		return "Unavailable For Legal Reasons";

	// 5xx Server Errors
	case HttpStatusCodes::InternalServerError:				return "Internal Server Error";
	case HttpStatusCodes::NotImplemented:					return "Not Implemented";
	case HttpStatusCodes::BadGateway:						return "Bad Gateway";
	case HttpStatusCodes::ServiceUnavailable:				return "Service Unavailable";
	case HttpStatusCodes::GatewayTimeout:					return "Gateway Timeout";
	case HttpStatusCodes::HTTPVersionNotSupported:			return "HTTP Version Not Supported";
	case HttpStatusCodes::VariantAlsoNegotiates:			return "Variant Also Negotiates";
	case HttpStatusCodes::InsufficientStorage:				return "Insufficient Storage";
	case HttpStatusCodes::LoopDetected:						return "Loop Detected";
	case HttpStatusCodes::NotExtended:						return "Not Extended";
	case HttpStatusCodes::NetworkAuthenticationRequired:	return "Network Authentication Required";
	default:
		// TODO CALLBACK метод перевода пользовательских кодов состояний
		return "";
	}
}

bool HttpResponse::WriteData(std::stringstream& ss) const
{
	ss.clear();
	
	// Head
	ss
		<< m_pRequest->m_sProtocolName << '/' << m_pRequest->m_sProtocolVersion << ' '
		<< m_nStatusCode << ' '
		<< TranslateStatusCode((HttpStatusCodes)m_nStatusCode)
		<< "\r\n";

	// Headers
	ss
		<< "Connection" << ": " << "Closed" << "\r\n";
	
	// Payload
	if (m_pBody)
	{
		auto len = strlen(m_pBody);
		if (len > 0)
		{
			ss
				<< "Content-Length: " << len << "\r\n"
				<< "Content-Type: " << m_psConentType->c_str() << "\r\n"
				<< "\r\n"
				<< m_pBody;
		}
	}

	return true;
}
