#pragma once

#include <fmt/format.h>

#include "core/math/vector.hpp"

template<>
struct fmt::formatter<Vin::Vector2<float>> {
	char presentation = 'f';

	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;
		if (it != end && *it != '}') throw format_error("invalid format");
		return it;
	}

	template <typename FormatContext>
	auto format(const Vin::Vector2<float>& vec, FormatContext& ctx) const -> decltype(ctx.out()) {
		return presentation == 'f'
			? fmt::format_to(ctx.out(), "({:.1f}, {:.1f})", vec.x, vec.y)
			: fmt::format_to(ctx.out(), "({:.1e}, {:.1e})", vec.x, vec.y);
	}
};

template<>
struct fmt::formatter<Vin::Vector3<float>> {
	char presentation = 'f';

	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;
		if (it != end && *it != '}') throw format_error("invalid format");
		return it;
	}

	template <typename FormatContext>
	auto format(const Vin::Vector3<float>& vec, FormatContext& ctx) const -> decltype(ctx.out()) {
		return presentation == 'f'
			? fmt::format_to(ctx.out(), "({:.1f}, {:.1f}, {:.1f})", vec.x, vec.y, vec.z)
			: fmt::format_to(ctx.out(), "({:.1e}, {:.1e}, {:.1e})", vec.x, vec.y, vec.z);
	}
};

template<>
struct fmt::formatter<Vin::Vector4<float>> {
	char presentation = 'f';

	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;
		if (it != end && *it != '}') throw format_error("invalid format");
		return it;
	}

	template <typename FormatContext>
	auto format(const Vin::Vector4<float>& vec, FormatContext& ctx) const -> decltype(ctx.out()) {
		return presentation == 'f'
			? fmt::format_to(ctx.out(), "({:.1f}, {:.1f}, {:.1f}, {:.1f})", vec.x, vec.y, vec.z, vec.w)
			: fmt::format_to(ctx.out(), "({:.1e}, {:.1e}, {:.1e})", vec.x, vec.y, vec.z, vec.w);
	}
};
