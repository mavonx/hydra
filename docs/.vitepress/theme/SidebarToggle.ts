import { defineComponent, h, onMounted, ref } from 'vue';

const KEY = 'sidebar-collapsed';

export default defineComponent({
  setup() {
    const collapsed = ref(false);

    const apply = (value: boolean) => {
      document.documentElement.classList.toggle('sidebar-collapsed', value);
    };

    onMounted(() => {
      try {
        collapsed.value = localStorage.getItem(KEY) === '1';
      } catch { }
      apply(collapsed.value);
    });

    const toggle = () => {
      collapsed.value = !collapsed.value;
      apply(collapsed.value);
      try {
        localStorage.setItem(KEY, collapsed.value ? '1' : '0');
      } catch { }
    };

    return () =>
      h(
        'button',
        {
          class: 'sidebar-toggle',
          type: 'button',
          'aria-label': collapsed.value ? 'Open sidebar' : 'Close sidebar',
          'aria-expanded': String(!collapsed.value),
          onClick: toggle
        },
        [
          h(
            'svg',
            {
              viewBox: '0 0 24 24',
              width: 18,
              height: 18,
              fill: 'none',
              stroke: 'currentColor',
              'stroke-width': 2,
              'stroke-linecap': 'round',
              'stroke-linejoin': 'round',
              'aria-hidden': 'true'
            },
            [h('path', { d: collapsed.value ? 'M9 6l6 6-6 6' : 'M15 6l-6 6 6 6' })]
          )
        ]
      );
  }
});
