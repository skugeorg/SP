import { Pane } from 'tweakpane';
export let fractalType = 1;
export const PARAMS = {
  color1: { r: 0, g: 100, b: 255 },
  color2: { r: 255, g: 50, b: 150 },
};
const pane = new Pane({
  title: 'Настройки объекта',
});
pane.addBinding(PARAMS, 'color1', {
  label: 'Цвет 1',
  color: { type: 'int' },
});
pane.addBinding(PARAMS, 'color2', {
  label: 'Цвет 2',
  color: { type: 'int' },
});
const btn = pane.addButton({
  title: 'Поменять фрактал',
});
btn.on('click', () => {
  // Изменили делитель с 2 на 4, чтобы циклически переключать 4 типа фракталов
  fractalType = (fractalType + 1) % 4;
});