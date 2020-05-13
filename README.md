# 구조체 멤버의 오프셋 얻기

> This repository is written in Korean.

간단한 구조체라면 직관적으로 그 구조체의 멤버의 위치, 크기를 알 수 있다.

```cpp
struct Hello
{
  int hello1; // size 4
  short hello2; // size 2
  double hello3; // size 8
};
```

그런데 문제는 아주~큰 구조체의 경우에는 이점이 쉽지 않다는 것이다. 예를 들자면 구조체 멤버가 천 개 정도인데 그 멤버들 중 일부는 또 구조체인 구조체라고 한다면 특정 멤버의 위치가 어느 정도인지 계산하기가 까다로울 수 밖에 없다.

```cpp
struct BigHello
{
  int hello1;
  // …
  int hello 100;
  // …
  double hello 199;
  Hello hello200;
  Hello hello201;
  // …
  Hello hello500;
  // …
}
```

그럴 경우를 위해서 자신만의 아래와 같은 매크로를 만들 수도 있다.

```cpp
#define OFFSETOF(a, b) ( (size_t) &((a)NULL)->b )
```

이 때, a 는 구조체의 포인터이고, b 는 멤버가 될 것이다.

약간 이상해 보이지만 c 의 포인터 개념을 알고 있다면 전혀 이상할 것은 없다. 임의의 구조체 대신에 NULL 을 가리키는 구조체 포인터a를 이용하여 멤버인 b가 무언지를 접근하는 매크로일 뿐이다. 실제 사용 방법은 아래와 같이 쓰면 될 것이다.

```cpp
struct HelloOffset
{
  long hello1;
  long hello2;
  double hello3;
};
```

```cpp
size_t s1 = offsetof(struct HelloOffset *, hello3); // 결과는 8 이다. (32bit OS)
```

그런데, offsetof() 라는 동일한 기능을 갖는 매크로가 이미 존재한다.

```cpp
// #include <stddef.h>

#ifdef _WIN64

#define offsetof(s,m) (size_t)( (ptrdiff_t)&reinterpret_cast<const volatile char&>((((s *)0)->m)) )

#else

#define offsetof(s,m) (size_t)&reinterpret_cast<const volatile char&>((((s *)0)->m))

#endif
```

위의 OFFSETOF() 보다는 타입 변환 등이 더 C++ 표준적인 요소가 많음을 알 수 있다.

- https://github.com/j2doll/offset-of-struct.kr
- https://j2doll.tistory.com/262
