# FirstGame - ДЗ 1: расширение Third Person Template

Unreal Engine 5.8. Проект на основе шаблона Third Person, расширенный C++ классом персонажа.

## Что сделано

- **Наследование.** C++ класс `AMyCharacter` (наследник `ACharacter`). Родитель `BP_ThirdPersonCharacter` заменён на него (File -> Reparent Blueprint), движение, камера и прыжок из шаблона работают как раньше.
- **Enhanced Input.** Созданы `IA_Sprint` (Left Shift) и `IA_Interact` (E) и добавлены в `IMC_Default`. Привязка через `BindAction` в `SetupPlayerInputComponent`. Ассеты назначены в Class Defaults `BP_ThirdPersonCharacter` (поля `SprintAction` и `InteractAction`).
- **Делегат.** `OnInteract` (Dynamic Multicast Delegate): вызывается (`Broadcast`) при нажатии E. В `BP_ThirdPersonCharacter` на него подписка (Bind Event to On Interact в Event BeginPlay), обработчик `HandleInteract` выводит `Interaction triggered!` через Print String.
- **Спринт.** При зажатом Left Shift `MaxWalkSpeed` увеличивается до `SprintSpeed` (1000), при отпускании возвращается обычная скорость. Состояние хранится в `bIsSprinting` (`UPROPERTY(BlueprintReadOnly)`).
- **Animation Blueprint.** В `ABP_Unarmed` добавлена переменная `bIsSprinting` (обновляется в Event Graph через Cast To MyCharacter), в State Machine добавлено состояние `Sprint` (анимация `MF_Unarmed_Jog_Fwd`, зациклена) с переходами `Locomotion <-> Sprint`. Переход в Sprint: `bIsSprinting AND ShouldMove`, обратно: `NOT (bIsSprinting AND ShouldMove)`. Условие `ShouldMove` нужно, чтобы при зажатом Shift на месте не проигрывалась анимация бега на месте.
- **Stamina.**
  - Переменная `Stamina` (`UPROPERTY(BlueprintReadOnly)`), максимум 100 (`MaxStamina`).
  - В `Tick`: пока идёт спринт и персонаж двигается, выносливость тратится (`StaminaDrainRate * DeltaTime`), иначе восстанавливается (`StaminaRegenRate * DeltaTime`) до максимума.
  - При `Stamina <= 0` вызывается `StopSprint()`, даже если Shift зажат.
  - `StartSprint` не запускает бег, если `Stamina` меньше `MinStaminaToSprint` (10).
  - Значение выводится на экран через `GEngine->AddOnScreenDebugMessage` (с проверкой `GEngine`).



## Параметры (можно менять в Class Defaults `BP_ThirdPersonCharacter`)


| Параметр             | Значение по умолчанию | Назначение                               |
| -------------------- | --------------------- | ---------------------------------------- |
| `SprintSpeed`        | 1000                  | скорость во время спринта                |
| `MaxStamina`         | 100                   | максимум выносливости                    |
| `StaminaDrainRate`   | 25                    | трата выносливости в секунду при спринте |
| `StaminaRegenRate`   | 15                    | восстановление в секунду                 |
| `MinStaminaToSprint` | 10                    | минимум для начала спринта               |




## Управление


| Клавиша    | Действие                                          |
| ---------- | ------------------------------------------------- |
| W A S D    | движение                                          |
| Мышь       | поворот камеры                                    |
| Space      | прыжок                                            |
| Left Shift | спринт                                            |
| E          | взаимодействие (надпись `Interaction triggered!`) |


