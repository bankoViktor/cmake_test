#include "../include/HttpResponse.h"
#include "../include/Utils.h"


HttpResponse::HttpResponse(const HttpRequest& request) :
	m_request(request)
{
	m_pszBody = nullptr;
	m_nStatusCode = (unsigned int)HttpStatusCodes::OK;
}

HttpResponse::~HttpResponse()
{
	SafeReleasePonter(m_pszBody);
}

void HttpResponse::Write(const char* content)
{
	SafeReleasePonter(m_pszBody);

	auto len = strlen(content) + 1;
	m_pszBody = new char[len];
	strcpy_s((char*)m_pszBody, len, content);
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

const HttpRequest& HttpResponse::GetRequest() const
{
	return m_request;
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
