# FirstGame - ДЗ 1: расширение Third Person Template

Unreal Engine 5.8. Проект на основе шаблона Third Person.

## Что сделано
- C++ класс `AMyCharacter` (наследник `ACharacter`). Родитель `BP_ThirdPersonCharacter` заменён на него.
- Enhanced Input: добавлены `IA_Sprint` (Left Shift) и `IA_Interact` (E) в `IMC_Default`. Привязка через `BindAction` в `SetupPlayerInputComponent`.
- Делегат `OnInteract` (Dynamic Multicast Delegate): вызывается (`Broadcast`) при нажатии E. В `BP_ThirdPersonCharacter` на него подписка и вывод `Interaction triggered!` через Print String.
- Спринт: при зажатом Left Shift увеличивается `MaxWalkSpeed`, при отпускании возвращается обычная скорость. Состояние хранится в `bIsSprinting` (`UPROPERTY(BlueprintReadOnly)`).
- Animation Blueprint: состояние Sprint в State Machine, переходы по `bIsSprinting`.

## Управление
| Клавиша | Действие |
|---|---|
| W A S D | движение |
| Мышь | поворот камеры |
| Space | прыжок |
| Left Shift | спринт |
| E | взаимодействие |
