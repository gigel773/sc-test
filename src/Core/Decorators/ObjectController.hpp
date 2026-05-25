#pragma once

#include <Interfaces/Object.hpp>

namespace sw::core::decorators
{

	class ObjectController final : public IObject
	{
	public:
		explicit ObjectController(Ptr impl);

		[[nodiscard]]
		uint32_t id() const override;

		[[nodiscard]]
		IAction::Ptr nextAction() const override;

		[[nodiscard]]
		ProcessingState processingState() const override;

		[[nodiscard]]
		std::string type() const override;

	private:
		Ptr _impl;
	};

}
