#include<vector>
#include"queue"
#include"Transaction.h"
class Pool {
private:
	std::queue<PTransaction> TransPool;
public:
	void AddTrans(PTransaction AddedTrans) {TransPool.push(AddedTrans);}
	void DeleteTrans(PTransaction AddedTrans) { TransPool.pop(); }
	PTransaction TopTrans() {
		return TransPool.front();
	}
};
typedef Pool* PPool;