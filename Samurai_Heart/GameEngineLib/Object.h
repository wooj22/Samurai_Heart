#pragma once

/* [Object 추상 클래스]
* 씬 안에 들어갈 모든 오브젝트의 base 타입이다.
* 각 Scene에 Object를 상속받은 다양한 클래스 객체들을 등록시키고,
* Scene은 자신의 Scene에 등록된 Object들의 update를 호출시킨다.
* 
* 즉, 다형성을 활용해 수많은 타입의 object들의 update를 일일히 호출시키지 않고
* Object class의 Update()로 한번에 update를 호출한다.
*/

class Object	// 추상 클래스
{
public:
	Object() = default;
	virtual ~Object() = default;    // 순수 가상 소멸자
	virtual void Start() = 0;   // 순수 가상 함수
	virtual void Update() = 0;	// 순수 가상 함수
	virtual void Render() = 0;	// 순수 가상 함수
};
