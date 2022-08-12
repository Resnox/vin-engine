#pragma once

#include "vinpch.hpp"

namespace Vin {
	enum class FileMode {
		None = 0,
		Read,
		Write,
		WriteAppend
	};

	/**
	 * GameFile class should manage Opening/Closing of file with RAII.
	 * GameFile class should refer to GameFilesystem class to know the root.
	 */
	class GameFile {
	public:
		virtual ~GameFile() {};

		virtual void Close() = 0;

		virtual char ReadByte() = 0;
		virtual size_t ReadBytes(char* buff, size_t count) = 0;
		virtual void WriteByte(char c) = 0;
		virtual void WriteBytes(char* buff, size_t count) = 0;

		virtual size_t GetSize() = 0;
		virtual bool IsEof() = 0;
		virtual size_t GetPos() = 0;
		virtual bool SetPos(size_t pos) = 0;

		template<typename T>
		T ReadType() {
			//Check size and handle validity
			T result{};
			ReadBytes((char*)(&result), sizeof(T));
			return result;
		}
		template<typename T>
		void WriteType(T value) {
			//Check handle validity
			WriteBytes((char*)(&value), sizeof(T));
		}
	};

	class GameFilesystem {
	public:
		static void Init();
		static void Terminate();
		static void Mount(const char* path);
		static bool Exists(const char* filepath);
		/**
		 * Open a file and return it's handle.
		 * Mod write should create the file if it doesn't exists.
		 * Mod WriteAppend should create the file if it doesn't exists.
		 *
		 * \return Return a valid file handle if success, -1 on failure.
		 */
		static std::unique_ptr<GameFile> Open(const char* filepath, FileMode mod);
		static void Delete(const char* filepath);

	protected:
		friend class PhysfsGameFilesystemApi;

		static class GameFilesystemApi {
		public:
			virtual ~GameFilesystemApi() {};

			virtual void Mount(const char* path) = 0;
			virtual bool Exists(const char* filepath) = 0;
			virtual std::unique_ptr<GameFile> Open(const char* filepath, FileMode mod) = 0;
			virtual void Delete(const char* filepath) = 0;
		} *s_GameFilesystemApi;
	};
}