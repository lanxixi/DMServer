#pragma once
class ProxyService : public DSService
{
public:

	virtual int init() override
	{
		//throw std::exception("The method or operation is not implemented.");
	}


	virtual void dispatch() override
	{
		//throw std::exception("The method or operation is not implemented.");
	}


	virtual void receive(const AMQP::Message &message) override
	{
		//throw std::exception("The method or operation is not implemented.");
	}


	virtual void stop(int reason) override
	{
		//throw std::exception("The method or operation is not implemented.");
	}

protected:

	virtual void onStart(int reason) override
	{
		//throw std::exception("The method or operation is not implemented.");
	}

private:
};