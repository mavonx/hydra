import { defineConfig } from 'vitepress';
import { withMermaid } from 'vitepress-plugin-mermaid';

export default withMermaid(
  defineConfig({
    base: '/hydra/',
    title: 'hydra',
    description: 'A fast, low-memory CLI for exploring massive CSV datasets without crashing.',
    lang: 'en-US',
    lastUpdated: true,
    cleanUrls: true,
    appearance: 'force-dark',
    vite: {
      optimizeDeps: {
        include: ['fastdom', 'mermaid']
      }
    },
    head: [
      ['link', { rel: 'icon', type: 'image/png', href: '/hydra/favicon.png' }],
      ['meta', { property: 'og:title', content: 'hydra' }],
      ['meta', { property: 'og:description', content: 'A fast, low-memory CLI for exploring massive CSV datasets without crashing.' }]
    ],
    themeConfig: {
      siteTitle: 'hydra',
      nav: [
        { text: 'Docs', link: '/docs' },
        { text: 'Installation', link: '/installation' },
        { text: 'Benchmarks', link: '/benchmarks' },
        { text: 'Examples', link: '/examples' },
        { text: 'GitHub', link: 'https://github.com/mavonx/hydra' }
      ],
      footer: {
        copyright: `Copyright © ${new Date().getFullYear()} mavonx`
      }
    },
    mermaid: {
      theme: 'dark'
    },
  })
);
