import { defineComponent, h, onMounted, ref } from 'vue';

export default defineComponent({
  setup() {
    const stars = ref('');

    onMounted(async () => {
      try {
        const cached = sessionStorage.getItem('stars');

        if (cached) {
          stars.value = cached;
          return;
        }

        const response = await fetch('https://api.github.com/repos/mavonx/hydra');
        if (!response.ok) return;

        const data = await response.json();
        stars.value = data.stargazers_count < 1000 ? String(data.stargazers_count) : `${(data.stargazers_count / 1000).toFixed(1).replace(/\.0$/, '')}k`;
        sessionStorage.setItem('stars', stars.value);
      } catch {
        return;
      }
    });

    return () =>
      h(
        'a',
        {
          class: 'github-stars',
          href: 'https://github.com/mavonx/hydra',
          target: '_blank',
          rel: 'noopener noreferrer',
          'aria-label': 'GitHub'
        },
        stars.value ? [h('span', { class: 'count' }, stars.value)] : []
      );
  }
});
