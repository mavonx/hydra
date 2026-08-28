import { defineConfig } from 'vitepress';
import { withMermaid } from 'vitepress-plugin-mermaid';

export default withMermaid(
  defineConfig({
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
      ['link', { rel: 'icon', href: '#' }],
      ['link', { rel: 'icon', type: 'image/png', href: '#' }],
      ['meta', { property: 'og:title', content: 'hydra' }],
      ['meta', { property: 'og:description', content: 'A fast, low-memory CLI for exploring massive CSV datasets without crashing.' }],
      ['meta', { property: 'og:image', content: '#' }],
      ['meta', { property: 'og:image:width', content: '1200' }],
      ['meta', { property: 'og:image:height', content: '630' }],
      ['meta', { property: 'twitter:card', content: 'summary_large_image' }],
      ['meta', { property: 'twitter:image', content: '#' }]
    ],
    themeConfig: {
      socialLinks: [
        { icon: 'github', link: 'https://github.com/mavonx/hydra' }
      ],
      footer: {
        copyright: `Copyright © ${new Date().getFullYear()} mavonx`
      }
    },
    mermaid: {
      theme: 'dark'
    }
  })
);
