# FirstGame - ДЗ 1: расширение Third Person Template

Unreal Engine 5.8. Проект на основе шаблона Third Person, расширенный C++ классом персонажа.

## Что сделано
- **Наследование.** C++ класс `AMyCharacter` (наследник `ACharacter`). Родитель `BP_ThirdPersonCharacter` заменён на него (File -> Reparent Blueprint), движение, камера и прыжок из шаблона работают как раньше.
- **Enhanced Input.** Созданы `IA_Sprint` (Left Shift) и `IA_Interact` (E) и добавлены в `IMC_Default`. Привязка через `BindAction` в `SetupPlayerInputComponent`. Ассеты назначены в Class Defaults `BP_ThirdPersonCharacter` (поля `SprintAction` и `InteractAction`).
- **Делегат.** `OnInteract` (Dynamic Multicast Delegate): вызывается (`Broadcast`) при нажатии E. В `BP_ThirdPersonCharacter` на него подписка (Bind Event to On Interact в Event BeginPlay), обработчик `HandleInteract` выводит `Interaction triggered!` через Print String.
- **Спринт.** При зажатом Left Shift `MaxWalkSpeed` увеличивается до `SprintSpeed` (1000), при отпускании возвращается обычная скорость. Состояние хранится в `bIsSprinting` (`UPROPERTY(BlueprintReadOnly)`).
- **Animation Blueprint.** В `ABP_Unarmed` добавлена переменная `bIsSprinting` (обновляется в Event Graph через Cast To MyCharacter), в State Machine добавлено состояние `Sprint` (анимация `MF_Unarmed_Jog_Fwd`, зациклена) с переходами `Locomotion <-> Sprint` по `bIsSprinting`.
- **Stamina (бонус).**
  - Переменная `Stamina` (`UPROPERTY(BlueprintReadOnly)`), максимум 100 (`MaxStamina`).
  - В `Tick`: пока идёт спринт и персонаж двигается, выносливость тратится (`StaminaDrainRate * DeltaTime`), иначе восстанавливается (`StaminaRegenRate * DeltaTime`) до максимума.
  - При `Stamina <= 0` вызывается `StopSprint()`, даже если Shift зажат.
  - `StartSprint` не запускает бег, если `Stamina` меньше `MinStaminaToSprint` (10).
  - Значение выводится на экран через `GEngine->AddOnScreenDebugMessage` (с проверкой `GEngine`).

## Параметры (можно менять в Class Defaults `BP_ThirdPersonCharacter`)
| Параметр | Значение по умолчанию | Назначение |
|---|---|---|
| `SprintSpeed` | 1000 | скорость во время спринта |
| `MaxStamina` | 100 | максимум выносливости |
| `StaminaDrainRate` | 25 | трата выносливости в секунду при спринте |
| `StaminaRegenRate` | 15 | восстановление в секунду |
| `MinStaminaToSprint` | 10 | минимум для начала спринта |

## Управление
| Клавиша | Действие |
|---|---|
| W A S D | движение |
| Мышь | поворот камеры |
| Space | прыжок |
| Left Shift | спринт |
| E | взаимодействие (надпись `Interaction triggered!`) |

## Основные файлы
- `Source/FirstGame/Public/MyCharacter.h`, `Source/FirstGame/Private/MyCharacter.cpp` - класс персонажа.
- `Content/ThirdPerson/Blueprints/BP_ThirdPersonCharacter` - Blueprint с подпиской на делегат.
- `Content/Characters/Mannequins/Anims/Unarmed/ABP_Unarmed` - Animation Blueprint со состоянием Sprint.
- `Content/Input` - Input Actions и `IMC_Default`.

## Как запустить
1. Открыть `FirstGame.uproject` в Unreal Engine 5.8 (при запросе пересобрать модули нажать «Да»).
2. Открыть уровень `Lvl_ThirdPerson` и нажать Play.
