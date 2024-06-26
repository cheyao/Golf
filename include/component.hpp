#pragma once

class Component {
       public:
	// (the lower the update order, the earlier the component updates)
	explicit Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void update(float delta);
	virtual void input();

	int getUpdateOrder() const { return mUpdateOrder; }

       protected:
	// Owner
	class Actor* mOwner;
	int mUpdateOrder;
};

