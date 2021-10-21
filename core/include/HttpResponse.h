#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include "HttpRequest.h"
#include "HttpHeaderCollection.h"
#include "export.h"
#include <string>
#include <memory>
#include <sstream>


typedef enum class _HttpStatusCodes
{
	// 1xx Informational 
	Continue						= 100,
	SwitchingProtocols				= 101,
	Processing						= 102,
	EarlyHints						= 103,

	// 2xx Success
	OK								= 200,
	Created							= 201,
	Accepted						= 202,
	NonAuthoritativeInformation		= 203,
	NoContent						= 204,
	ResetContent					= 205,
	PartialContent					= 206,
	MultiStatus						= 207,
	AlreadyReported					= 208,
	IMUsed							= 226,

	// 3xx Redirection
	MultipleChoices					= 300,
	MovedPermanently				= 301,
	Found							= 302,	// Previously "Moved Temporarily"
	MovedTemporarily				= 302,
	SeeOther						= 303,
	NotModified						= 304,
	UseProxy						= 305,
	SwitchProxy						= 306,
	TemporaryRedirect				= 307,
	PermanentRedirect				= 308,

	// 4xx Client Errors
	BadRequest						= 400,
	Unauthorized					= 401,
	PaymentRequired					= 402,
	Forbidden						= 403,
	NotFound						= 404,
	MethodNotAllowed				= 405,
	NotAcceptable					= 406,
	ProxyAuthenticationRequired		= 407,
	RequestTimeout					= 408,
	Conflict						= 409,
	Gone							= 410,
	LengthRequired					= 411,
	PreconditionFailed				= 412,
	PayloadTooLarge					= 413,
	URITooLong						= 414,
	UnsupportedMediaType			= 415,
	RangeNotSatisfiable				= 416,
	ExpectationFailed				= 417,
	IAmTeapot						= 418,
	MisdirectedRequest				= 421,
	UnprocessableEntity				= 422,
	Locked							= 423,
	FailedDependency				= 424,
	TooEarly						= 425,
	UpgradeRequired					= 426,
	PreconditionRequired			= 428,
	TooManyRequests					= 429,
	RequestHeaderFieldsTooLarge		= 431,
	UnavailableForLegalReasons		= 451,

	// 5xx Server Errors
	InternalServerError				= 500,
	NotImplemented					= 501,
	BadGateway						= 502,
	ServiceUnavailable				= 503,
	GatewayTimeout					= 504,
	HTTPVersionNotSupported			= 505,
	VariantAlsoNegotiates			= 506,
	InsufficientStorage				= 507,
	LoopDetected					= 508,
	NotExtended						= 510,
	NetworkAuthenticationRequired	= 511,
} HttpStatusCodes;


class DLLEXPORTED HttpResponse
{
private:
	const HttpRequest* m_pRequest;
	const char* m_pBody;
	std::string* m_psConentType;
	unsigned int m_nStatusCode;

public:
	HttpResponse(const HttpRequest &request);
	~HttpResponse();
	void Write(const char* content, const char* conentType);
	void Write(const std::string& content, const std::string& conentType);
	void SetStatusCode(HttpStatusCodes statusCode);
	void SetStatusCode(unsigned int statusCode);
	unsigned int GetStatusCode() const;
	const HttpRequest* GetRequest() const;
	static const char* TranslateStatusCode(HttpStatusCodes status);

	bool WriteData(std::stringstream& ss) const;
};


#endif // !_HTTP_RESPONSE_H
