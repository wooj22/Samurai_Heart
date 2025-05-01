#pragma once

/* [Object �߻� Ŭ����]
* �� �ȿ� �� ��� ������Ʈ�� base Ÿ���̴�.
* �� Scene�� Object�� ��ӹ��� �پ��� Ŭ���� ��ü���� ��Ͻ�Ű��,
* Scene�� �ڽ��� Scene�� ��ϵ� Object���� update�� ȣ���Ų��.
* 
* ��, �������� Ȱ���� ������ Ÿ���� object���� update�� ������ ȣ���Ű�� �ʰ�
* Object class�� Update()�� �ѹ��� update�� ȣ���Ѵ�.
*/

class Object	// �߻� Ŭ����
{
public:
	Object() = default;
	virtual ~Object() = default;      // ���� ���� �Ҹ���
	virtual void Start() = 0; // ���� ���� �Լ�
	virtual void Update() = 0;	// ���� ���� �Լ�
	virtual void Render() = 0;	// ���� ���� �Լ�
};
