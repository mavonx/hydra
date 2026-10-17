import { defineConfig } from 'vitepress';
import { withMermaid } from 'vitepress-plugin-mermaid';

export default withMermaid(
  defineConfig({
    base: '/hydra/',
    title: 'hydra',
    titleTemplate: ':title - hydra',
    description: 'A fast, low-memory CLI for exploring massive CSV datasets without crashing.',
    cleanUrls: true,
    appearance: 'force-dark',
    transformPageData(pageData) {
      if (pageData.relativePath === 'index.md') {
        pageData.titleTemplate = false;
      }
    },
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
      sidebar: [
        {
          text: 'Introduction',
          items: [
            { text: 'What is hydra', link: '/introduction/what-is-hydra' },
            { text: 'Installation', link: '/introduction/installation' },
            { text: 'Quick start', link: '/introduction/quick-start' }
          ]
        },
        {
          text: 'Commands',
          items: [
            { text: 'Overview', link: '/commands/overview' },
            { text: 'Opening a file', link: '/commands/open-file' },
            { text: 'File metadata', link: '/commands/file-metadata' }
          ]
        },
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
