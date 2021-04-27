#pragma once

#ifdef _DEBUG
#define LOGERROR(...)		Log::Error(__VA_ARGS__)
#define LOGINFO(...)		Log::Info(__VA_ARGS__)
#define LOGWARNING(...)		Log::Warning(__VA_ARGS__)
#define LOGTRACE(...)		Log::Trace(__VA_ARGS__)
#else	
#define LOGERROR(...) 
#define LOGINFO(...) 
#define LOGWARNING(...) 
#define LOGTRACE(...) 
#endif

class Log
{
private:
	using Color = unsigned short;
	enum : Color { Red = 12, Green = 10, Yellow = 14, Blue = 9, Magenta = 13, Cyan = 11, White = 15 };
private:
	static Color currentColor;
public:

	template<typename ...M>
	static void Error(const M& ...message)
	{
		LogType("|ERROR|", Red);
		LogMessage(message...);
	}

	template<typename ...M>
	static void Info(const M& ...message)
	{
		LogType("|INFO|", Yellow);
		LogMessage(message...);
	}

	template<typename ...M>
	static void Warning(const M& ...message)
	{
		LogType("|WARNING|", Magenta);
		LogMessage(message...);
	}

	template<typename ...M>
	static void Trace(const M& ...message)
	{
		LogType("|TRACE|", Blue);
		LogMessage(message...);
	}

private:
	static void LogType(const std::string& logType, const Color& color);

	template<typename M>
	static void LogMessage(const M& message)
	{
		std::cout << message << std::endl;
	}

	template<typename M, typename ...A>
	static void LogMessage(const M& message, const A& ...args)
	{
		std::cout << message << ' ';
		LogMessage(args...);
	}

};

